# scripts/copy_fw.py
Import("env")               # required so 'env' is available
import os, shutil

OUT = os.path.join(".pio", "build", "wokwi")
os.makedirs(OUT, exist_ok=True)

def _copy_to_wokwi(target, source, env):
    src = str(target[0])
    if not os.path.exists(src):
        print(f"[wokwi] WARN: build artifact not found: {src}")
        return
    dst = os.path.join(OUT, os.path.basename(src))
    shutil.copy2(src, dst)
    print(f"[wokwi] copied {src} -> {dst}")

# run after build finishes producing these files
env.AddPostAction("$BUILD_DIR/${PROGNAME}.bin", _copy_to_wokwi)
env.AddPostAction("$BUILD_DIR/${PROGNAME}.elf", _copy_to_wokwi)
