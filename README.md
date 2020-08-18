# ezip
AES Encrypion and Compression 
### Installation
```bash
    snowden@NSA:~$ make main
```
### Usage
Encryption is simple with ezip. Just use the `-oe` flag to tell ezip you want to encrypt. 
Use the `-f` flag to specify which file.
```bash
    snowden@NSA:~$ ./ezip -oe -f test-data/meme4.jpg
```
Decrypting is just as easy. Just use the `.ezip` and `.key` files generated from the encryption.
This time we will use the `-od` to specify we want to decrypt. Additionally we will use the `-k`
to tell ezip where the key is.
```bash
    snowden@NSA:~$ ./ezip -od -f meme4.jpg.ezip -k meme4.jpg.key
```
### AES Explained
### Key Generation
### Compression