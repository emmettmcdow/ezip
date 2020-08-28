# ezip
AES Encrypion and Compression using gzip. This was a fun project for me, so I would not recommend using it in any professional setting. However it is perfect for learning how the process of encryption works. The majority of the code is commented and I made a pretty low-level write up of the techniques that went into it. Have fun!
### Installation
Firstly install some dependencies. You will need [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page), and [Boost](https://www.boost.org). Also make sure that you can run C++17 and have make, and cmake installed. Then run this
```bash
snowden@NSA:~/ezip$ mkdir build
snowden@NSA:~/ezip$ cd build
snowden@NSA:~/ezip/build$ cmake ..
snowden@NSA:~/ezip/build$ make ..
```
Then you should be able to run ezip from your build folder.
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
AES is the type of encryption used in ezip. It stands for Advanced Encryption Standard,
and is generally regarded as a good balance between security and speed for most applications.
The math upon which it is based is pretty complicated, however you don't really need to be
able to understand that math to be able to understand how exactly it works. AES is considered
a symmetric private key encryption standard. Which means that you will use the same key for 
both encryption and decryption. There are essentially 4 different operations that we use to 
scramble up our data. 
1. Substitute Bytes
2. Shift Rows
3. Mix Columns
4. Add Round Key
For ezip, we use 128-bit encryption, which simply put means that we will run 10 rounds of our
operations. This also means that to decrypt, we will simply do the reverse order inverse of those
operations. We also want to put our data into blocks of 16-bytes, represented as a 4x4 matrix
of bytes.
#### Substitute Bytes
Fun fact, AES is a specific implementation of a protocol named Rijndael, created by 
[Vincent Rijmen](https://en.wikipedia.org/wiki/Vincent_Rijmen) and [Joan Daemen](https://en.wikipedia.org/wiki/Joan_Daemen).
As a result, the substitute bytes step takes advantage of something called the Rijndael S-box.
This is a static box that you can use to replace each byte in your original data with a corresponding
byte in the S-box. [Insert Image]. It is important to use this specific S-box because there is some
really smart math that is behind it that assures that your data is properly mixed up. You 
can  read about it [here](https://en.wikipedia.org/wiki/Rijndael_S-box). 
#### Shift Rows
Shift rows is pretty straightforward because we simply shift each of the rows of the data
matrix by a preset amount. The first row we shift 0 times, the second 1 time, and so on. ![](https://user-images.githubusercontent.com/24411516/90669331-7dc2bf80-e21f-11ea-89d5-4e601f5ff0d3.png)
#### Mix Columns
Mix Columns is in my opinion one of the more complicated parts of the whole AES algorithm. I will
do my best to explain in layman's terms, but [here](https://en.wikipedia.org/wiki/Rijndael_MixColumns)
is a link to an explanation in more detail. Essentially we are multiplying our data matrix by
a preset 4x4 matrix. Instead of addition, we use a xor, and instead of multiplication we use
multiplication over the Galois Field G(F^8). <br/> ![](https://user-images.githubusercontent.com/24411516/90670130-bc0cae80-e220-11ea-9794-3ebd3d40810d.png) <br/> In this example, the column corresponding to b
is multiplied by the matrix and we get a new column d to put in its place.
#### Add Round Key
Add Round Key is the step that makes sure that no two cyphers are ever the same. We take our original
key, and expand it a number of times equal to the number of steps of encryption we have. We
expand it in this way. <br/> ![](https://user-images.githubusercontent.com/24411516/90669377-90d58f80-e21f-11ea-83f3-d3882eafc083.png) <br/>![](https://user-images.githubusercontent.com/24411516/90670066-a1d2d080-e220-11ea-914c-fff0191b439f.png) <br/> ![](https://user-images.githubusercontent.com/24411516/90671128-4275c000-e222-11ea-8959-109b7a7aa1d9.png) <br/>RotWord is loosely equivalent to the rotation in shift rows' second row. And
SubWord uses the S-box to replace each byte with one from the S-box.For each of the rounds we xor the round key
with each word of our data. That way different keys result in 
different cypher text, in addition to the generous mixing and replacing we outlined above.
### Key Generation
### Compression
