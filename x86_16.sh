#!/bin/sh
sed  '3s/^/\n#ifdef X86_16\n  __asm__(".code16gcc\\n")\n#endif\n/'  *.h
#sed -i '3s/^/\n#ifdef X86_16\n  __asm__(".code16gcc\\n")\n#endif\n/'  *.h
