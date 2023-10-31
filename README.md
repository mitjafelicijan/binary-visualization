# Visualization of binary files

![Preview](https://github.com/mitjafelicijan/binary-visualization/assets/296714/8c7e016c-8f58-4af1-9cce-9f4366219bbe)

This repository holds solutions for expriments for binary file visualization and
reverse engineering of binary data. It is inspired by [TED talk by Chris
Domas](https://www.ted.com/talks/chris_domas_the_1s_and_0s_behind_cyber_warfare).

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
  songs in Public Domain was choosen. I extracted 10 seconds from 30th second on
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
