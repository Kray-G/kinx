#include "dss.h"

const char *dss_instr_type_str[6] = {
	"arithmetic", "logical", "data processing", "stack", "conditional branch", "unconditional branch"
};

void parse_sem_file(const char *file, struct hash_table *stable)
{
	FILE *fp = fopen(file, "r");
	if (!fp) {
		printf("Error opening semantic file %s\n", file);
		return;
	}
	fseek(fp, 0, SEEK_END);
	int len = ftell(fp);
	if (len < 0) {
		printf("Error seeking in file\n");
		fclose(fp);
		return;
	}
	rewind(fp);
	char *buffer = malloc(len+1);
	memset(buffer, 0, len);
	if (fread(buffer, 1, len, fp) != (size_t)len) {
		printf("Error reading from file\n");
		fclose(fp);
		free(buffer);
		return;
	}
	buffer[len] = 0;
	char *tbuf = buffer; /*Malleable ptr for parsing function*/
	struct dsem *sem = NULL;
	while ((sem=parse_semantic(&tbuf))) {
		hash_table_insert(stable, hash_entry_init(sem->mnemonic, sem));
	}
	free(buffer);
	fclose(fp);
}

struct dsem *parse_semantic(char **buffer)
{
	char *buf = *buffer;
	if (!buf) return NULL;
	char *save_ptr = strchr(buf, '\n');
	char *line = buf;
	if (!line || !save_ptr) return NULL;
	*save_ptr = 0;
	save_ptr++;
	struct dsem *sem = NULL;
	do {
		if (!sem) {/*If semantic is NULL, try and the starting line of "[mnem] grp-id"*/
			char *dstr = strchr(line, ']');
			if (!dstr) continue;
			dstr[0] = 0;
			dstr++;
			char *mstr = strchr(line, '[');
			if (!mstr) continue;
			mstr++;
			int v = strtol(dstr, NULL, 10);
			sem = dsem_init(mstr, v);
		/*Otherwise try and read the read/write flag/operand lines*/
		} else if (!strncmp(line, "o:", 2)) {
			parse_rwoperands(sem, line+2);
		} else if (!strncmp(line, "i:", 2)) {
			parse_rwimplied(sem, line+2);
		} else if (!strncmp(line, "f:", 2)) {
			parse_rwflags(sem, line+2);
		}
	} while ((line=save_ptr) && (save_ptr=strchr(save_ptr, '\n')) && (*save_ptr=0,save_ptr++) && !!strncmp(line, "end", 3));
	*buffer = save_ptr;
	return sem;
}

void parse_rwoperands(struct dsem *sem, char *line)
{
	int len = strlen(line);
	char *val = line;
	while (val!=(line+len)) {
		char *rw = strchr(val, '$');
		if (!rw) break;
		rw++;
		val = strchr(val, '=');
		if (!val) break;
		val++;
		val = strchr(val, '$');
		if (!val) break;
		val++;
		int amask = 0;
		while (*rw=='r'||*rw=='w') {
			amask |= *rw=='r'?DSEM_READ:DSEM_WRITE;
			rw++;
		}
		dsem_add(sem, strtol(val, NULL, 0), amask);
	}
}

void parse_rwimplied(struct dsem *sem, char *line)
{
	int len = strlen(line);
	char *val = line;
	while (val != (line+len)) {
		char *rw = strchr(val, '$');
		if (!rw) break;
		rw++;
		val = strchr(val, '=');
		if (!val) break;
		val++;
		val = strchr(val, '\"');
		if (!val) break;
		val++;
		int amask = 0;
		while (*rw == 'r' || *rw == 'w') {
			amask |= *rw == 'r'?DSEM_READ:DSEM_WRITE;
			rw++;
		}
		char *vend = strchr(val, '\"');
		if (!vend) break;
		*vend = '\0';
		dsem_addi(sem, val, amask);
	}
}

void parse_rwflags(struct dsem *sem, char *line)
{
	int len = strlen(line);
	char *val = line;
	while (val && val!=(line+len) && *val) {
		char *ft = strchr(val, '$');
		if (!ft) return;
		val = strchr(val, '=');
		if (!val) return;
		val++;
		unsigned char flags = 0;
		int fv = 0;
		while ((fv=val[0])) {
			flags |= FVAL(fv);
			val++;
		}
		if (!strncmp(ft, "$mf", 3))
			sem->mflags |= flags;
		if (!strncmp(ft, "$rf", 3))
			sem->rflags |= flags;
	}
}

struct dsem *dsem_init(char *mnemonic, int group)
{
	struct dsem *sem = malloc(sizeof(struct dsem));
	sem->group = group, sem->rflags = 0, sem->mflags = 0;
	int len = strlen(mnemonic);
	sem->mnemonic = malloc(len+1);
	strncpy(sem->mnemonic, mnemonic, len);
	sem->mnemonic[len] = 0;
	sem->read = NULL, sem->nread = 0;
	sem->write = NULL, sem->nwrite = 0;
	sem->implw = NULL, sem->nimplw = 0;
	sem->implr = NULL, sem->nimplr = 0;
	return sem;
}

void dsem_destroy(struct dsem *sem)
{
	if (!sem) return;
	for (int i = 0; i < sem->nimplr; i++)
		free(sem->implr[i]);
	for (int i = 0; i < sem->nimplw; i++)
		free(sem->implw[i]);
	free(sem->implr);
	free(sem->implw);
	free(sem->read);
	free(sem->write);
	free(sem->mnemonic);
	free(sem);
}

void dsem_add(struct dsem *sem, int val, int rw)
{
	if (rw & DSEM_READ) {
		sem->nread++;
		if (!sem->read)
			sem->read=malloc(sizeof(int));
		else
			sem->read=realloc(sem->read, sizeof(int)*sem->nread);
		sem->read[sem->nread-1] = val;
	}
	if (rw & DSEM_WRITE) {
		sem->nwrite++;
		if (!sem->write)
			sem->write=malloc(sizeof(int));
		else
			sem->write=realloc(sem->write, sizeof(int)*sem->nwrite);
		sem->write[sem->nwrite-1] = val;
	}
}

void dsem_addi(struct dsem *sem, char *val, int rw)
{
	int len = strlen(val);
	if (rw & DSEM_READ) {
		sem->nimplr++;
		if (!sem->implr)
			sem->implr=malloc(sizeof(char*));
		else
			sem->implr=realloc(sem->implr, sizeof(int)*sem->nimplr);
		char *vc = malloc(len+1);
		strncpy(vc, val, len);
		vc[len] = 0;
		sem->implr[sem->nimplr-1] = vc;
	}
	if (rw & DSEM_WRITE) {
		sem->nimplw++;
		if (!sem->implw)
			sem->implw=malloc(sizeof(char*));
		else
			sem->implw=realloc(sem->implw, sizeof(char*)*sem->nimplw);
		char *vc = malloc(len+1);
		strncpy(vc, val, len);
		vc[len] = 0;
		sem->implw[sem->nimplw-1] = vc;
	}
}

void dsem_print(struct dsem *sem)
{
	if (!sem) return;
	printf("MNEMONIC: %s\tGROUP: %d : %s\n", sem->mnemonic, sem->group, dss_instr_type_str[sem->group]);
	printf("READ: ");
	for (int i = 0; i < sem->nread; i++) {
		printf("opr_%d%c", sem->read[i], (i+1)==sem->nread?'\n':',');
	}
	printf("WRITE: ");
	for (int i = 0; i < sem->nwrite; i++) {
		printf("opr_%d%c", sem->write[i], (i+1)==sem->nwrite?'\n':',');
	}
	printf("Modified Flags: ");
	for (int i = 7; sem->mflags && i >= 0; i--) {
		int val = sem->mflags & (1 << i);
		printf("%c", VALF(val));
	}
	printf("\n");
	printf("Read Flags: ");
	for (int i = 7; sem->rflags && i >= 0; i--) {
		int val = sem->rflags & (1 << i);
		printf("%c", VALF(val));
	}
	printf("\n");
}

void print_semantics(struct dis *dis, struct dsem *sem)
{
	if (!dis || !sem) return;
	printf("Disassembly: \"%s  %s\"\n", dis->mnemonic, dis->op_squash);
	printf("Mnemonic: %s\nSemantic Group: %s\n", sem->mnemonic, dss_instr_type_str[sem->group]);
	char buf[64];
	if (sem->nread)
		printf("READ: ");
	for (int i = 0; i < sem->nread; i++) {
		if (sem->read[i] >= dis->num_operands) continue;
		operand_squash(buf, 64, dis->operands[sem->read[i]]);
		printf("%s%c", buf, (i+1)==sem->nread?'\n':',');
	}
	if (sem->nwrite)
		printf("WRITE: ");
	for (int i = 0; i < sem->nwrite; i++) {
		if (sem->write[i] >= dis->num_operands) continue;
		operand_squash(buf, 64, dis->operands[sem->write[i]]);
		printf("%s%c", buf, (i+1)==sem->nwrite?'\n':',');
	}
	if (sem->nimplr)
		printf("IMPLIED READ: ");
	for (int i = 0; i < sem->nimplr; i++) {
		printf("%s%c", sem->implr[i], (i+1)==sem->nimplr?'\n':',');
	}
	if (sem->nimplw)
		printf("IMPLIED WRITE: ");
	for (int i = 0; i < sem->nimplw; i++) {
		printf("%s%c", sem->implw[i], (i+1)==sem->nimplw?'\n':',');
	}
	if (sem->mflags) printf("Modified Flags: ");
	for (int i = 7; sem->mflags && i >= 0; i--) {
		int val = sem->mflags & (1 << i);
		printf("%c", VALF(val));
	}
	if (sem->mflags) printf("\n");
	if (sem->rflags) printf("Read Flags: ");
	for (int i = 7; sem->rflags && i >= 0; i--) {
		int val = sem->rflags & (1 << i);
		printf("%c", VALF(val));
	}
	if (sem->rflags) printf("\n");
	printf("\n");
}
