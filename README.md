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
Lalu untuk menangkap ketikan dari user menggunakan loop while(1) dimana ini akan terus berjalan dengan beberapa perintah yaitu:  
- Enter (\n atau \n) = akan memberikan tanda penutup (\0) dan keluar melalui break
- Backspace (\b) = akan memundurkan kursor di layar dan menghapus ketikan dengan menimpanya pakai spasi
- Ngetik seperti yang ditampilkan di layar menggunakan printChar
Selain itu fungsi lainnya berguna untuk menyocokan dua kata (misal menyocokan ketikan dengan kata "help")

```c
int startsWith(char* str, char* prefix) {
    int i = 0;
    while (prefix[i] != '\0') {
        if (str[i] != prefix[i]) {
            return 0;
        }
        i++;
    }
    return 1;
}

int atoi(char* str) {
    int res = 0;
    int i = 0;

    while (str[i] == ' ') i++;

    while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9') {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return res;
}
```
Selanjutnya adalah fungsi untuk ngecek huruf awalan. Ia melakukan looping hanya sepanjang huruf awalan yang dicari. Kalau nyari awalan "add ", dia cuma ngecek 4 huruf pertama. Dan selanjutnya yaitu fungsi yang mengubah teks jadi angka untuk dibaca sistem.

```c
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

        while (temp_n >= 10) {
            temp_n -= 10;
            q++;
        }
        r = temp_n;

        temp[i] = r + '0';
        i++;
        n = q;
    }

    j = 0;
    while (i > 0) {
        i--;
        buf[j] = temp[i];
        j++;
    }
    buf[j] = '\0';
}
```

Fungsi intToString bertugas mengonversi tipe data integer menjadi string agar hasilnya bisa ditampilkan di layar
