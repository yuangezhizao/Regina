# Regina firmware Cloud Agent base image.
# Mirrors the project's own .devcontainer, which builds on Espressif's official
# ESP-IDF image. Pinned to release-v5.5 to match the primary (non-experimental)
# toolchain exercised by .github/workflows/build-esp-idf-project.yml.
FROM espressif/idf:release-v5.5

ENV LC_ALL=C.UTF-8
ENV LANG=C.UTF-8

# The agent runs as root in this image; let git operate on the checked-out
# workspace without tripping the "dubious ownership" guard.
RUN git config --system --add safe.directory '*'

# Make idf.py, esptool and the cross toolchains available in interactive shells.
RUN echo '. /opt/esp/idf/export.sh > /dev/null 2>&1' >> /root/.bashrc
