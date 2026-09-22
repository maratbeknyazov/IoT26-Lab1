#!/usr/bin/env bash
set -euo pipefail

echo "[setup_codespace] start"

# Ensure running from repo root (postCreateCommand runs in repo root already)
REPO_ROOT="$(pwd)"
echo "[setup_codespace] repo root: $REPO_ROOT"

# 1) Ensure python3 exists
if ! command -v python3 >/dev/null 2>&1; then
  echo "[setup_codespace] python3 not found. Aborting."
  exit 1
fi

# 2) Upgrade pip and install PlatformIO CLI into user site
echo "[setup_codespace] upgrading pip and installing platformio (user install)"
python3 -m pip install --upgrade pip --user
python3 -m pip install --user -U platformio

# 3) Make sure ~/.local/bin is on PATH for this script
export PATH="$HOME/.local/bin:$PATH"
echo "[setup_codespace] PATH=$PATH"

# 4) Verify pio is available
if ! command -v pio >/dev/null 2>&1; then
  echo "[setup_codespace] ERROR: 'pio' not found after install. Exiting."
  exit 1
fi
echo "[setup_codespace] platformio version: $(pio --version || true)"

# 5) Optional: update platformio core/platforms (non-fatal)
echo "[setup_codespace] running 'pio update' (this may take a while)"
pio update || echo "[setup_codespace] warning: 'pio update' failed or returned non-zero (continuing)"

# 6) Extract default_envs from platformio.ini (if present)
DEFAULT_ENV=""
if [ -f platformio.ini ]; then
  DEFAULT_ENV=$(python3 - <<'PY'
import configparser
cfg = configparser.ConfigParser()
cfg.read('platformio.ini')
env = ''
if 'platformio' in cfg:
    env = cfg['platformio'].get('default_envs', '').strip()
# print exactly what's found (may be empty)
print(env)
PY
)
fi

if [ -z "$DEFAULT_ENV" ]; then
  echo "[setup_codespace] No default_envs found in platformio.ini. Skipping build step."
else
  echo "[setup_codespace] Found default_envs: '$DEFAULT_ENV' — starting build"
  # run the build; do not abort provisioning if build fails, but print error
  if ! pio run -e "$DEFAULT_ENV"; then
    echo "[setup_codespace] WARNING: pio build failed for env '$DEFAULT_ENV' (continuing)"
  else
    echo "[setup_codespace] pio build succeeded for env '$DEFAULT_ENV'"
  fi
fi

echo "[setup_codespace] done" 

