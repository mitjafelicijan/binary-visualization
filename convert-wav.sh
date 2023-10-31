#!/bin/bash

set -xe

for file in data/audio/mp3/*.mp3; do
    basename=$(basename "$file" .mp3)
    wav_file="data/audio/wav/${basename}.wav"
    ffmpeg -y -i "$file" -ss 30 -t 10 "$wav_file"
done
