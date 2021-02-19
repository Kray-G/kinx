#ifndef KX_KXTHREAD_H
#define KX_KXTHREAD_H

#if defined(_WIN32) && !defined(__CYGWIN__)
#define USE_WINDOWS
#endif

#if defined(USE_WINDOWS)

#include <windows.h>
#include <process.h>
#include <time.h>

#define sleep(x) Sleep((x)*1000)
#define strtok_r strtok_s
#define STDCALL __stdcall
typedef unsigned thread_return_t;
typedef thread_return_t (__stdcall* thread_func_t)(void*);
typedef BOOL (WINAPI* signal_handler_func_t)(DWORD);
typedef HANDLE pthread_t;
typedef CRITICAL_SECTION pthread_mutex_t;
typedef struct { HANDLE signal, broadcast; } pthread_cond_t;
#if _MSC_VER <= 1600
struct timespec { time_t tv_sec/* sec */; long tv_nsec/* nanosec */; };
#endif
#define pthread_self() GetCurrentThreadId()

static inline int pthread_mutex_init(pthread_mutex_t* mutex, void* unused)
{
    (void)unused;
    InitializeCriticalSection(mutex);
    return 0;
}

static inline int pthread_mutex_destroy(pthread_mutex_t* mutex)
{
    DeleteCriticalSection(mutex);
    return 0;
}

static inline int pthread_mutex_lock(pthread_mutex_t* mutex)
{
    EnterCriticalSection(mutex);
    return 0;
}

static inline int pthread_mutex_trylock(pthread_mutex_t* mutex)
{
    if (TryEnterCriticalSection(mutex)) {
        return 0;   // success.
    }
    return EBUSY;
}

static inline int pthread_mutex_unlock(pthread_mutex_t* mutex)
{
    LeaveCriticalSection(mutex);
    return 0;
}

static inline int pthread_join(pthread_t thid, void* unused)
{
    (void)unused;
    int waitret  = WaitForSingleObject(thid, INFINITE) == WAIT_OBJECT_0;
    int closeret = CloseHandle(thid) != 0;
    return (waitret && closeret) ? 0 : -1;
}

static inline int pthread_create_extra(pthread_t* thid, thread_func_t f, void* p, int stacksize)
{
    unsigned int threadid = 0;
    *thid = (HANDLE)_beginthreadex(NULL, stacksize, f, p ,0, &threadid);
    return (*thid == 0) ? -1 : 0;
}

static inline void msec_sleep(int msec)
{
    Sleep(msec);
}

static inline int pthread_cond_init(pthread_cond_t* cv, const void* unused)
{
    (void)unused;
    cv->signal    = CreateEvent(NULL, FALSE, FALSE, NULL);
    cv->broadcast = CreateEvent(NULL, TRUE,  FALSE, NULL);
    return cv->signal != NULL && cv->broadcast != NULL ? 0 : -1;
}

static inline int pthread_cond_wait(pthread_cond_t* cv, pthread_mutex_t* mutex)
{
    HANDLE handles[] = { cv->signal, cv->broadcast };
    pthread_mutex_unlock(mutex);
    WaitForMultipleObjects(2, handles, FALSE, INFINITE);
    return pthread_mutex_lock(mutex);
}

static inline int pthread_cond_timedwait(pthread_cond_t* cv, pthread_mutex_t* mutex, const struct timespec* abstime)
{
    int msec = (abstime->tv_sec - time(0)) * 1000 + abstime->tv_nsec / 1000;
    HANDLE handles[] = { cv->signal, cv->broadcast };
    pthread_mutex_unlock(mutex);
    WaitForMultipleObjects(2, handles, FALSE, msec);
    return pthread_mutex_lock(mutex);
}

static inline int pthread_cond_signal(pthread_cond_t* cv)
{
    return SetEvent(cv->signal) == 0 ? -1 : 0;
}

static inline int pthread_cond_broadcast(pthread_cond_t* cv)
{
    return PulseEvent(cv->broadcast) == 0 ? -1 : 0;
}

static inline int pthread_cond_destroy(pthread_cond_t* cv)
{
    return CloseHandle(cv->signal) && CloseHandle(cv->broadcast) ? 0 : -1;
}

#else

#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#define STDCALL
typedef void* thread_return_t;
typedef thread_return_t (*thread_func_t)(void*);

static inline int pthread_create_extra(pthread_t* thid, thread_func_t f, void* p, int stacksize)
{
    pthread_attr_t attr;

    if (pthread_attr_init(&attr)) return -1;
    if (stacksize > 0) {
        if (pthread_attr_setstacksize(&attr, stacksize)) {
            return -1;
        }
    }

    int ret = pthread_create(thid, &attr, f, p);
    if (ret == -1) {
        return -1;
    }

    pthread_attr_destroy(&attr);
    return 0;
}

static inline void msec_sleep(int msec)
{
    struct timespec req;
    req.tv_sec  = (int)(msec / 1000);
    req.tv_nsec = 1000000 * ((int)(msec % 1000));
    nanosleep(&req, NULL);
}

#endif // USE_WINDOWS

#ifndef KX_DLL
extern pthread_mutex_t g_mutex;
#endif

#endif /* KX_KXTHREAD_H */
