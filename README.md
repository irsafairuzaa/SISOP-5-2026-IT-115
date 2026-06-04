# LAPORAN PRAKTIKUM SISOP MODUL 5
Nama: Irsa Fairuza  
NRP: 5027251115
## Soal 2
Untuk memulai pembuatan bochs kita mengisi fungsi getChar_ di file kernel.c dengan kode sebagai berikut
```c
mov ah, 0       ; Menyiapkan instruksi BIOS untuk menunggu tombol ditekan
int 0x16        ; Memanggil interupsi keyboard (Interrupt 16h)
ret             ; Kembali ke program C dengan membawa kode karakter di register AL
```
Disini kita menyiapkan instruksi BIOS untuk menunggu tombol ditekan user dilanjut dengan memanggil interupsi keyboar yaitu interupt 16h. Selanjutnya kembali ke program C dengan membawa kode karakter di register.  

  Selanjutnya, untuk bisa menggunakan bochs kita mengisi file kernel.c dengan kode-kode berikut
  ```c
void newline() {
    int sisa = cursor;
    while (sisa >= 80) {
        sisa -= 80;
    }
    cursor += (80 - sisa);

void printChar(char c) {
    if (c == '\n' || c == '\r') {
        newline();
    } else {
        putInMemory(0xB000, 0x8000 + cursor * 2, c);
        putInMemory(0xB000, 0x8001 + cursor * 2, color);
        cursor++;
    }
}
}
```
Ini sebagai tombol enter di bochs, yang bertugas memindahkan kursor ke baris bawahnya  
```c
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
    cursor = 0;
}
```
Selanjutnya fungsi ini sebagai pencetak kata atau kalimat panjang dengan melakukan looping untuk mencetak huruf satu per satu sampai bertemu karakter '/0' yang menandakan kalimatnya sudah selesai. Lalu dibawahnya yaitu fungsi seperti penghapusan, ia akan menimpa semua kotak di layar dengan spasi kosong (' '). Setelah layarnya bersih, kursornya dikembalikan lagi ke angka 0 (pojok kiri atas) biar siap dipakai ngetik dari awal lagi.

```c
void readString(char* buf) {
    int i = 0;
    char c = 0;

    while (1) {
        c = getChar();

        if (c == '\r' || c == '\n') {
            buf[i] = '\0';
            break;
        } else if (c == '\b') {
            if (i > 0) {
                i--;
                cursor--; 
                putInMemory(0xB000, 0x8000 + cursor * 2, ' ');
                putInMemory(0xB000, 0x8001 + cursor * 2, color);
            }
        } else {
            buf[i] = c;
            i++;
            printChar(c);
        }
    }
}

int strcmp(char* s1, char* s2) {
    int i = 0;
    while (s1[i] == s2[i]) {
        if (s1[i] == '\0') {
            return 1;
        }
        i++;
    }
    return 0;
}
```
Lalu untuk menangkap ketikan dari user menggunakan loop while(1) dimana ini akan terus berjalan 
