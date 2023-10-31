![Preview](https://github.com/mitjafelicijan/binary-visualization/assets/296714/d7dd736f-7061-4314-8d2e-86b2dc89de62)

# Visualization of binary files

This repository holds solutions for experiments for binary file visualization
and reverse engineering of binary data. It is inspired by [TED talk by Chris
Domas](https://www.ted.com/talks/chris_domas_the_1s_and_0s_behind_cyber_warfare).

## Running this locally

The application is written in C and should work with most compilers. I tested it
with GCC, Clang and TinyCC.

```sh
# compile first
CC=clang make -B
```

If this step is successful I provide couple of example that can be executed with
`bash payload.sh payload.image.txt`. Check `payload.image.txt` to see what is
happening there.

But you can also execute it directly.

```sh
$ ./digraph
Usage: ./digraph -t type -i <input file> -o <output file>
```

There are two types of inputs. One is `image` and the other one is
`other`. Image is a special case because most of the modern formats compress
images and the result is nothings like interpreting raw images. So in this case
image is being decompressed and then visualized.

Same goes with audio files. Mp3 files I provided for example are also by nature
of Mp3's compressed and that is why I also converted them into WAV files.

## Testing data

All data, but binaries (since they are system programs) is available in `data`
folder in this repository so feel free to browse.

- All images are from https://unsplash.com/ and resized to 512x512. But you can
  use any size possible for testing. I resized them to keep tests quick and
  filesizes small.
- For x86-64 binaries I choose binaries from Fedora 38 `/bin/` folder.
- For darwin-arm64 binaries I choose binaries from Macbook Air M1 `/bin/`
  folder.
- Audio was selected from [Open Music Archive](http://openmusicarchive.org/) and
  songs in Public Domain was chosen. I extracted 10 seconds from 30th second on
  to keep WAV files small. Mp3 and WAV was tested.
  - Clara Smith - Court House Blues
  - Virginia Liston - I'm Gonna Get Me A Man That's All
  - Pine Top Smith - Jump Steady Blues
  - Virginia Liston - Night Latch Key Blues
  - Edna Hicks - Poor Me Blues
  - Blind Lemon Jefferson - One Dime Blues
  - Jim Jackson - Old Dog Blue
  - Coley Jones - Drunkard's Special
  - Johnny Dodds Trio - Little Bits
  - The Masked Marvel - Mississippi Boweavil Blues
  - Prince Albert Hunt's Texas Ramblers - Wake Up Jacob
  - George Lewis & His New Orleans Stompers - Don't Go 'Way Nobody

## Special thanks

- Sean Barrett for creating [STB libraries](https://github.com/nothings/stb).
- [Tsoding](https://twitter.com/tsoding) for introducing me to this method.
