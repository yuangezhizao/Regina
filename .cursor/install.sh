#!/usr/bin/env bash
# Idempotent repository bootstrap for the Regina ESP-IDF firmware.
# Runs from the repository root after checkout.
set -euo pipefail

# Locate and source the ESP-IDF environment (idf.py, esptool, cmake, ninja, RISC-V toolchain).
idf_export=""
for cand in "${IDF_PATH:-}/export.sh" "/opt/esp/idf/export.sh" "${HOME}/esp/esp-idf/export.sh"; do
    if [ -n "${cand}" ] && [ -f "${cand}" ]; then
        idf_export="${cand}"
        break
    fi
done
if [ -z "${idf_export}" ]; then
    echo "ERROR: could not find ESP-IDF export.sh. Is ESP-IDF installed?" >&2
    exit 1
fi
# export.sh is not written for `set -u`; relax it only while sourcing.
set +u
# shellcheck disable=SC1090
. "${idf_export}"
set -u

# Fetch the pinned dependency components (idempotent: existing clones are skipped).
python3 fetch_repos.py

# Warm the build: download managed components (arduino-esp32) and compile the firmware
# once so subsequent agent builds are incremental.
(
    cd platforms/Regina
    idf.py set-target esp32c6 build
)

echo "Regina firmware environment is ready. Build again with: cd platforms/Regina && idf.py build"
