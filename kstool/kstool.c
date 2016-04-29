// Kstool for Keystone Assembler Engine.
// By Nguyen Anh Quynh, 2016
#include <stdio.h>
#include <string.h>

#include <keystone/keystone.h>

#define VERSION "1.0"

static void usage(char *prog)
{
    printf("Kstool v%s for Keystone Assembler Engine (www.keystone-engine.org)\nBy Nguyen Anh Quynh, 2016\n\n", VERSION);
    printf("Syntax: %s <arch+mode> <assembly-string>\n", prog);
    printf("\n  The following <arch+mode> options are supported:\n");
    printf("        x16:       X86 16bit, Intel syntax\n");
    printf("        x32:       X86 32bit, Intel syntax\n");
    printf("        x64:       X86 64bit, Intel syntax\n");
    printf("        x16att:    X86 16bit, AT&T syntax\n");
    printf("        x32att:    X86 32bit, AT&T syntax\n");
    printf("        x64att:    X86 64bit, AT&T syntax\n");
    printf("        arm:       ARM - little endian\n");
    printf("        armbe:     ARM - big endian\n");
    printf("        thumb:     Thumb - little endian\n");
    printf("        thumbbe:   Thumb - big endian\n");
    printf("        arm64:     AArch64\n");
    printf("        hexagon:   Hexagon\n");
    printf("        mips:      Mips - little endian\n");
    printf("        mipsbe:    Mips - big endian\n");
    printf("        mips64:    Mips64 - little endian\n");
    printf("        mips64be:  Mips64 - big endian\n");
    printf("        ppc32be:   PowerPC32 - big endian\n");
    printf("        ppc64:     PowerPC64 - little endian\n");
    printf("        ppc64be:   PowerPC64 - big endian\n");
    printf("        sparc:     Sparc - little endian\n");
    printf("        sparcbe:   Sparc - big endian\n");
    printf("        sparc64:   Sparc64 - little endian\n");
    printf("        sparc64be: Sparc64 - big endian\n");
    printf("        systemz:   SystemZ (S390x)\n");
}

int main(int argc, char **argv)
{
    ks_engine *ks;
    ks_err err = KS_ERR_ARCH;
    char *mode, *assembly;
    size_t count;
    unsigned char *insn;
    size_t size;

    if (argc != 3) {
        usage(argv[0]);
        return -1;
    }

    mode = argv[1];
    assembly = argv[2];

    if (!strcmp(mode, "x16")) {
        err = ks_open(KS_ARCH_X86, KS_MODE_16, &ks);
    }
    if (!strcmp(mode, "x32")) {
        err = ks_open(KS_ARCH_X86, KS_MODE_32, &ks);
    }
    if (!strcmp(mode, "x64")) {
        err = ks_open(KS_ARCH_X86, KS_MODE_64, &ks);
    }
    if (!strcmp(mode, "x16att")) {
        err = ks_open(KS_ARCH_X86, KS_MODE_16, &ks);
        if (!err) {
            ks_option(ks, KS_OPT_SYNTAX, KS_OPT_SYNTAX_ATT);
        }
    }
    if (!strcmp(mode, "x32att")) {
        err = ks_open(KS_ARCH_X86, KS_MODE_32, &ks);
        if (!err) {
            ks_option(ks, KS_OPT_SYNTAX, KS_OPT_SYNTAX_ATT);
        }
    }
    if (!strcmp(mode, "x64att")) {
        err = ks_open(KS_ARCH_X86, KS_MODE_64, &ks);
        if (!err) {
            ks_option(ks, KS_OPT_SYNTAX, KS_OPT_SYNTAX_ATT);
        }
    }
    if (!strcmp(mode, "arm")) {
        err = ks_open(KS_ARCH_ARM, KS_MODE_ARM+KS_MODE_LITTLE_ENDIAN, &ks);
    }
    if (!strcmp(mode, "armbe")) {
        err = ks_open(KS_ARCH_ARM, KS_MODE_ARM+KS_MODE_BIG_ENDIAN, &ks);
    }
    if (!strcmp(mode, "thumb")) {
        err = ks_open(KS_ARCH_ARM, KS_MODE_THUMB+KS_MODE_LITTLE_ENDIAN, &ks);
    }
    if (!strcmp(mode, "thumbbe")) {
        err = ks_open(KS_ARCH_ARM, KS_MODE_THUMB+KS_MODE_BIG_ENDIAN, &ks);
    }
    if (!strcmp(mode, "arm64be") || !strcmp(mode, "arm64")) {
        err = ks_open(KS_ARCH_ARM64, KS_MODE_BIG_ENDIAN, &ks);
    }
    if (!strcmp(mode, "hex") || !strcmp(mode, "hexagon")) {
        err = ks_open(KS_ARCH_HEXAGON, KS_MODE_BIG_ENDIAN, &ks);
    }
    if (!strcmp(mode, "mips")) {
        err = ks_open(KS_ARCH_MIPS, KS_MODE_MIPS32+KS_MODE_LITTLE_ENDIAN, &ks);
    }
    if (!strcmp(mode, "mipsbe")) {
        err = ks_open(KS_ARCH_MIPS, KS_MODE_MIPS32+KS_MODE_BIG_ENDIAN, &ks);
    }
    if (!strcmp(mode, "mips64")) {
        err = ks_open(KS_ARCH_MIPS, KS_MODE_MIPS64+KS_MODE_LITTLE_ENDIAN, &ks);
    }
    if (!strcmp(mode, "mips64be")) {
        err = ks_open(KS_ARCH_MIPS, KS_MODE_MIPS64+KS_MODE_BIG_ENDIAN, &ks);
    }
    if (!strcmp(mode, "ppc32be")) {
        err = ks_open(KS_ARCH_PPC, KS_MODE_PPC32+KS_MODE_BIG_ENDIAN, &ks);
    }
    if (!strcmp(mode, "ppc64")) {
        err = ks_open(KS_ARCH_PPC, KS_MODE_PPC64+KS_MODE_LITTLE_ENDIAN, &ks);
    }
    if (!strcmp(mode, "ppc64be")) {
        err = ks_open(KS_ARCH_PPC, KS_MODE_PPC64+KS_MODE_BIG_ENDIAN, &ks);
    }
    if (!strcmp(mode, "sparc")) {
        err = ks_open(KS_ARCH_SPARC, KS_MODE_SPARC32+KS_MODE_LITTLE_ENDIAN, &ks);
    }
    if (!strcmp(mode, "sparcbe")) {
        err = ks_open(KS_ARCH_SPARC, KS_MODE_SPARC32+KS_MODE_BIG_ENDIAN, &ks);
    }
    if (!strcmp(mode, "sparc64")) {
        err = ks_open(KS_ARCH_SPARC, KS_MODE_SPARC64+KS_MODE_LITTLE_ENDIAN, &ks);
    }
    if (!strcmp(mode, "sparc64be")) {
        err = ks_open(KS_ARCH_SPARC, KS_MODE_SPARC64+KS_MODE_BIG_ENDIAN, &ks);
    }
    if (!strcmp(mode, "systemz") || !strcmp(mode, "sysz") || !strcmp(mode, "s390x")) {
        err = ks_open(KS_ARCH_SYSTEMZ, KS_MODE_BIG_ENDIAN, &ks);
    }

    if (err) {
        printf("ERROR: failed on ks_open()\n");
        usage(argv[0]);
        return -1;
    }

    if (ks_asm(ks, assembly, 0, &insn, &size, &count)) {
        printf("ERROR: failed on ks_asm() with count = %lu, error = '%s' (code = %u)\n", count, ks_strerror(ks_errno(ks)), ks_errno(ks));
    } else {
        size_t i;
        printf("Kstool for Keystone Engine (www.keystone-engine.org)\n\n");

        printf("%s = [ ", assembly);
        for (i = 0; i < size; i++) {
            printf("%02x ", insn[i]);
        }
        printf("]\n");
        //printf("Assembled: %lu bytes, %lu statement(s)\n", size, count);
    }

    // NOTE: free insn after usage to avoid leaking memory
    ks_free(insn);

    // close Keystone instance when done
    ks_close(ks);

    return 0;
}