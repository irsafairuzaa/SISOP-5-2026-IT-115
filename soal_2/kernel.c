int cursor = 0;
char color = 0x07;

void putInMemory(int segment, int address, char character);
int getChar();

/*
 * Final Challenge
 *
 * Commands:
 * - check
 * - add <a> <b>
 * - sub <a> <b>
 * - fac <n>
 * - season <name>
 * - triangle <n>
 * - clear
 * - about
 *
 * Season list:
 * - winter
 * - spring
 * - summer
 * - fall
 * - radiant
 *
 * Restrictions:
 * - no stdlib
 * - avoid division (/)
 * - avoid modulo (%)
 */

/*
 * TODO:
 * 1. printChar()
 * 2. printString()
 * 3. clearScreen()
 * 4. readString()
 * 5. strcmp()
 * 6. startsWith()
 * 7. atoi()
 * 8. intToString()
 * 9. factorial()
 * 10. add handler
 * 11. sub handler
 * 12. fac handler
 * 13. season handler
 * 14. triangle handler
 * 15. shell loop
 */

void newline() {
    int sisa = cursor;
    /* Mencari sisa bagi (modulus) manual dari 80 (lebar layar) */
    while (sisa >= 80) {
        sisa -= 80;
    }
    /* Geser kursor ke awal baris berikutnya */
    cursor += (80 - sisa);
}

void printChar(char c) {
    if (c == '\n' || c == '\r') {
        newline();
    } else {
        /* Memasukkan karakter dan warna ke memori VGA */
        putInMemory(0xB000, 0x8000 + cursor * 2, c);
        putInMemory(0xB000, 0x8001 + cursor * 2, color);
        cursor++;
    }
}

void printString(char* str) {
    int i = 0;
    while (str[i] != '\0') {
        printChar(str[i]);
        i++;
    }
}

void clearScreen() {
    int i = 0;
    while (i < 2000) {
        putInMemory(0xB000, 0x8000 + i * 2, ' ');
        putInMemory(0xB000, 0x8001 + i * 2, color);
        i++;
    }
    cursor = 0; /* Kembalikan kursor ke pojok kiri atas */
}

void readString(char* buf) {
    int i = 0;
    char c = 0;

    while (1) {
        c = getChar(); // Membaca satu karakter dari hardware

        if (c == '\r' || c == '\n') {
            /* Jika tombol Enter ditekan */
            buf[i] = '\0'; // Tutup string
            break;
        } else if (c == '\b') {
            /* Jika tombol Backspace ditekan */
            if (i > 0) {
                i--;
                cursor--; // Mundurkan kursor
                /* Timpa layar dengan spasi agar hurufnya hilang secara visual */
                putInMemory(0xB000, 0x8000 + cursor * 2, ' ');
                putInMemory(0xB000, 0x8001 + cursor * 2, color);
            }
        } else {
            /* Karakter biasa */
            buf[i] = c;
            i++;
            printChar(c); // Tampilkan huruf yang sedang diketik ke layar
        }
    }
}

int strcmp(char* s1, char* s2) {
    int i = 0;
    while (s1[i] == s2[i]) {
        if (s1[i] == '\0') {
            return 1; /* Sama persis (True) */
        }
        i++;
    }
    return 0; /* Beda (False) */
}

int startsWith(char* str, char* prefix) {
    int i = 0;
    while (prefix[i] != '\0') {
        if (str[i] != prefix[i]) {
            return 0; /* False */
        }
        i++;
    }
    return 1; /* True */
}

int atoi(char* str) {
    int res = 0;
    int i = 0;

    /* Lewati spasi jika ada */
    while (str[i] == ' ') i++;

    while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9') {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return res;
}

void intToString(int n, char* buf) {
    char temp[16];
    int i = 0;
    int q, r, temp_n;
    int j;

    if (n == 0) {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }

    while (n > 0) {
        q = 0;
        temp_n = n;

        /* Proses "Pembagian" dan "Modulo" manual pakai pengurangan 10 */
        while (temp_n >= 10) {
            temp_n -= 10;
            q++;
        }
        r = temp_n; /* Sisanya adalah modulo */

        temp[i] = r + '0'; /* Ubah angka satuan jadi karakter */
        i++;
        n = q; /* Lanjutkan dengan hasil baginya */
    }

    /* Balikkan urutan string-nya karena didapat dari belakang */
    j = 0;
    while (i > 0) {
        i--;
        buf[j] = temp[i];
        j++;
    }
    buf[j] = '\0';
}

void main() {

    char cmd[64];

    clearScreen();

    printString("Welcome to Assistant's Last Gift\r\n");
    newline();

    printString("type 'help'");
    newline();
    newline();

    while (1) {

        printString("> ");

        readString(cmd);

        newline();

        /*
         * TODO:
         * command handler
         *
         * example:
         *
         * if (strcmp(cmd, "check")) {
         *     printString("ok");
         * }
         */

        if (strcmp(cmd, "check")) {
            printString("ok");
        } else if (strcmp(cmd, "help")) {
            printString("check add sub fac season triangle clear about");
        } else if (strcmp(cmd, "clear")) {
            clearScreen();
        } else if (cmd[0] != '\0') {
            printString("Command not found!");
        }

        newline();
    }
}
