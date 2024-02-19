#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE_OPCODE_COUNT 14
#define EXT_OPCODE_COUNT 21

typedef struct {
    char key[5];
    unsigned char opcode;
} StaticOpcode;

StaticOpcode baseOpcodes[BASE_OPCODE_COUNT] = {
	{ .key = "daa", .opcode = 0x27 },
	{ .key = "exx", .opcode = 0xd9 },
	{ .key = "ccf", .opcode = 0x3f },
	{ .key = "di", .opcode = 0xf3 },
	{ .key = "ei", .opcode = 0xfb },
	{ .key = "scf", .opcode = 0x37 },
	{ .key = "rla", .opcode = 0x17 },
	{ .key = "rlca", .opcode = 0x07 },
	{ .key = "cpl", .opcode = 0x2f },
	{ .key = "rra", .opcode = 0x1f },
	{ .key = "rrca", .opcode = 0x0f },
	{ .key = "ret", .opcode = 0xc9 },
	{ .key = "nop", .opcode = 0x00 },
	{ .key = "halt", .opcode = 0x76 },
};

StaticOpcode extOpcodes[EXT_OPCODE_COUNT] = {
	{ .key = "reti", .opcode = 0x4d },
	{ .key = "inir", .opcode = 0xb2 },
	{ .key = "otdr", .opcode = 0xbb },
	{ .key = "outd", .opcode = 0xab },
	{ .key = "retn", .opcode = 0x45 },
	{ .key = "otir", .opcode = 0xb3 },
	{ .key = "outi", .opcode = 0xa3 },
	{ .key = "ldd", .opcode = 0xa8 },
	{ .key = "cpd", .opcode = 0xa9 },
	{ .key = "ldi", .opcode = 0xa0 },
	{ .key = "neg", .opcode = 0x44 },
	{ .key = "ind", .opcode = 0xaa },
	{ .key = "cpi", .opcode = 0xa1 },
	{ .key = "rld", .opcode = 0x6f },
	{ .key = "ini", .opcode = 0xa2 },
	{ .key = "rrd", .opcode = 0x67 },
	{ .key = "lddr", .opcode = 0xb8 },
	{ .key = "cpdr", .opcode = 0xb9 },
	{ .key = "ldir", .opcode = 0xb0 },
	{ .key = "indr", .opcode = 0xba },
	{ .key = "cpir", .opcode = 0xb1 },
};

StaticOpcode *search_static_opcodes(char *key, StaticOpcode *arr, unsigned char length) {
    for (int i = 0; i < length; i++) {
        if (strcmp(arr[i].key, key) == 0) {
            return &arr[i];
        }
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    char buffer[16];

    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    int inputLength = strlen(buffer);

    if (inputLength < 2 || inputLength > 4) {
        printf("Invalid mnemonic\n");
        return 1;
    }

    StaticOpcode *found = search_static_opcodes(buffer, baseOpcodes, BASE_OPCODE_COUNT);
    if (found == NULL && inputLength > 2) {
        found = search_static_opcodes(buffer, extOpcodes, EXT_OPCODE_COUNT);
    }

    if (found != NULL) {
        printf("%02x\n", found->opcode);
    }
    else {
        printf("Invalid mnemonic\n");
    }

    return 0;
}
