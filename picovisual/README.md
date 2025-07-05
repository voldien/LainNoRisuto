#

## Build Instruction

```bash
cmake -DPICO_BOARD=pico2 DPICO_PLATFORM=rp2350 ..
```

```bash
cmake -DCMAKE_BUILD_TYPE=Debug -DPICO_BOARD=pico2 ..
```

```bash
cmake -DCMAKE_BUILD_TYPE=Debug -DPICO_BOARD=pico2 -DCMAKE_BUILD_TYPE=Release ..
```

## Upload Instruction

```bash
picotool load -v -x firmware/pico-visual.uf2 
```

```bash
sudo openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c "program firmware/pico-visual.elf verify reset exit"
```

```bash
sudo openocd -f interface/cmsis-dap.cfg -f target/rp2350.cfg -c "adapter speed 5000" -c "program firmware/pico-visual.elf verify reset exit"
```
