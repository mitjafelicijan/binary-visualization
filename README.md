# Visualization of binary files

![Preview](https://github.com/mitjafelicijan/binary-visualization/assets/296714/55003089-5696-4ba7-8ee3-d6046a80ed23)

This repository holds solutions for expriments for binary file visualization and
reverse engineering of binary data. It is inspired by [TED talk by Chris
Domas](https://www.ted.com/talks/chris_domas_the_1s_and_0s_behind_cyber_warfare).

## Testing data

- All images are from https://unsplash.com/ and resized to 512x512. But you can
  use any size possible for testing. I resized them to keep tests quick and
  filesizes small.
- For x86-64 binaries I choose binaries from Fedora 38 `/bin/` folder.
- For darwin-arm64 binaries I choose binaries from Macbook Air M1 `/bin/`
  folder.

## Special thanks

- Sean Barrett for creating [STB libraries](https://github.com/nothings/stb).
- [Tsoding](https://twitter.com/tsoding) for introducing me to this method.
