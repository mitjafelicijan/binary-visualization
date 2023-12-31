![Digraphs](./assets/digraphs.png)

# Visualization of binary files

This repository holds solutions for experiments with binary file visualization
and reverse engineering of binary data. It is inspired by [TED talk by Chris
Domas](https://www.ted.com/talks/chris_domas_the_1s_and_0s_behind_cyber_warfare).

In the context of directed graphs, commonly referred to as digraphs, data can be
processed and visualized in a unique manner. Specifically, binary files
containing relevant data are read into the system, and this data is subsequently
extracted in the form of tuples. These tuples represent ordered pairs of values
that can be utilized to denote specific points or coordinates. Once the tuples
have been extracted, they are then translated onto a Cartesian plane.

## Running this locally

The application is written in C and should work with most compilers. I tested it
with GCC, Clang and TinyCC.

```sh
# compile first
CC=clang make digraph -B
CC=clang make trigraph -B
```

If this step is successful I provide couple of example that can be executed with
`bash payload.sh digraph payload.image.txt`. Check `payload.image.txt` to see what is
happening there.

But you can also execute it directly.

```sh
$ ./digraph
Usage: ./digraph -t type -i <input file> -o <output file>
Usage: ./trigraph -t type -i <input file> -o <output file>
```

There are two types of inputs. One is `image` and the other one is
`other`. Image is a special case because most of the modern formats compress
images and the result is nothing like interpreting raw images. So in this case
image is being decompressed and then visualized.

Same goes with audio files. Mp3 files I provided for example are also by nature
of Mp3's compressed and that is why I also converted them into WAV files.

## 3D view of the files

![Trigraphs](./assets/trigraphs.gif)

Folder `www` contains `3d-point-cloud.html`. This reads `*.pc` files from `out`
folder and generates 3D point cloud.

This can also be seen at https://mitjafelicijan.github.io/binary-visualization/.

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
- All the text for testing ASCII was used from [Project
  Gutenberg](https://www.gutenberg.org/browse/scores/top) since this material is
  in Public Domain.
  - Frankenstein; Or, The Modern Prometheus by Mary Wollstonecraft Shelley (4234)
  - Romeo and Juliet by William Shakespeare (1908)
  - Pride and Prejudice by Jane Austen (1907)
  - The Scarlet Letter by Nathaniel Hawthorne (1787)
  - Dracula by Bram Stoker (1320)
  - The Great Gatsby by F. Scott Fitzgerald (1237)
  - Alice's Adventures in Wonderland by Lewis Carroll (1196)
  - A Doll's House: a play by Henrik Ibsen (1042)
  - Metamorphosis by Franz Kafka (963)
  - The Strange Case of Dr. Jekyll and Mr. Hyde by Robert Louis Stevenson (962)
  - The Yellow Wallpaper by Charlotte Perkins Gilman (927)
  - A Modest Proposal by Jonathan Swift (924)

## Special thanks

- Sean Barrett for creating [STB libraries](https://github.com/nothings/stb).
- [Tsoding](https://twitter.com/tsoding) for introducing me to this method.
