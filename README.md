# ft_ssl_md5

An introduction to cryptographic hashing algorithms

This project consists of recoded versions of the message-digest algorithm MD5.

Built from the ground up using only these functions:

* open, close
* read, write
* malloc, free
* strerror, exit

## Installation:

`git clone https://github.com/chimpansiets/ft_ssl_md5.git && cd ft_ssl_md5 && make`

## Examples:

Mimics the behaviour of the `md5` utility:

```
echo -n "hello world" | ./ft_ssl md5
5eb63bbbe01eeed093cb22bb8f5acdc3
```

```
echo "MD5 was designed by Ronald Rivest in 1991" | ./ft_ssl md5 -p
MD5 was designed by Ronald Rivest in 1991
b10422a016cb412cc9d432ff3c05e238
```

```
./ft_ssl md5 main.c
MD5 (main.c) = 5c9752527df82f35affe6f423fd48a15
```
