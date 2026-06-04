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
}
```
Ini sebagai tombol enter di bochs, yang bertugas memindahkan teks baris ke bawahnya
