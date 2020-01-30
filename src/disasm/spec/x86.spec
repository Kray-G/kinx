[adc] 0
o: $rw = $0, $r = $1
f: $rf=.......c
f: $mf=o..szapc
end

[sbb] 0
o: $rw = $0, $r = $1
f: $rf=.......c
f: $mf=o..szapc
end

[add] 0
o: $rw = $0, $r = $1
f: $mf=o..szapc
end

[sub] 0
o: $rw = $0, $r = $1
f: $mf=o..szapc
end

[imul] 0
o: $rw = $0, $r = $1, $r = $2
f: $mf=o..szapc
end

[cmp] 0
o: $r = $0, $r = $1
f: $mf=o..szapc
end

[or] 1
o: $rw = $0, $r = $1
f: $rf=........
f: $mf=o..sz.pc
end

[and] 1
o: $rw = $0, $r = $1
f: $mf=o..szapc
end

[xor] 1
o: $rw = $0, $r = $1
f: $mf=o..szapc
end

[jb] 4
o: $r = $0
f: $rf=.......c
end

[jnb] 4
o: $r = $0
f: $rf=.......c
end

[jz] 4
o: $r = $0
f: $rf=....z...
end

[jnz] 4
o: $r = $0
f: $rf=....z...
end

[jl] 4
o: $r = $0
f: $rf=o..s....
end

[jle] 4
o: $r = $0
f: $rf=o..sz...
end

[jge] 4
o: $r = $0
f: $rf=o..s....
end

[jg] 4
o: $r = $0
f: $rf=o..sz...
end

[mov] 2
o: $w = $0, $r = $1
end

[push] 3
i: $rw = "esp"
o: $r = $0
end

[pop] 3
i: $rw = "esp"
o: $w = $0
end
