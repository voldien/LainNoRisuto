#

## Build Instruction

```bash
cmake -DPICO_BOARD=pico DPICO_PLATFORM=rp2350 ..
```

## Upload Instruction

```bash
picotool load -v -x firmware/pico-visual.uf2 
```