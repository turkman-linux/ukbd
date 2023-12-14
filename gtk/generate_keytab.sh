#!/bin/bash
echo '#define str_check(A, B, C) if(iseq(A,B)){return C;}'
echo '#define iseq(A,B) strcmp(A,B)==0'
echo '#include <string.h>'
echo 'char* str_to_label(char* str) {'
cat /usr/include/X11/keysymdef.h | grep "^#define " | tr -s " " | while read line ; do
    label=$(echo "$line" | cut -f2 -d" " | sed "s/^XK_//g")
    code=$(echo "$line" | cut -f5 -d" " | grep "^U+")
    code=$(printf "${code/U+/"\U"}")
    if echo $line | grep "deprecated" >/dev/null ; then
        echo "    str_check(str, \"$label\", \"\");"
    fi
    elif [[ "$code" != "" && "$code" != "$label" ]] ; then
        echo "    str_check(str, \"$label\", \"$code\");"
    fi
done | sed 's/\\/\\\\/g' | sed 's/"""/"\\""/g'
echo '    return str;'
echo '}'
