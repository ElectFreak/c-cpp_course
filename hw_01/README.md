# BMP Image Editor

This project is a command-line tool written in C++ that allows you to perform basic image editing operations on BMP images.

### Console application

Compile project:
```bash
make
```

The application is started with the following command:

```bash
./hw_01 crop-rotate 'in-bmp' 'out-bmp' 'x' 'y' 'w' 'h'
```

Parameters used:

- `crop-rotate` is a mandatory parameter indicating the action to be performed.
- `in-bmp` - name of the input image file.
- `out-bmp` - name of the output image file.
- `x`, `y` - coordinates of the upper left corner of the area to be cut and rotated. The coordinates start from zero, so _(0, 0)_ is the upper left corner.
- `w`, `h` - width and height of the area before rotation.

To save the secret string to the image, the application is started with the following command:
```bash
./hw_01 insert 'in-bmp' 'out-bmp' 'key-txt' 'msg-txt'
```

To extract the secret string from the image, the application is run with the following command:
```bash
./hw_01 extract 'in-bmp' 'key-txt' 'msg-txt'
```

Parameters used:

* `in-bmp` - name of the input image file.
* `out-bmp` - name of the output image file.
* `key-txt` - test file with key.
* `msg-txt` - text file with secret message.
