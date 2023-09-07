# Apptainer on the linux-cluster

## Build docker container locally and push to dockerhub

```
docker build -f Dockerfile -t sebwolf/mypi:latest
docker push sebwolf/mypi
```

## Install a lot of stuff on the linux-cluster manually
* ninja
* meson
* fuse
* squashfuse (needs some patching, assuming you install your libraries in `$HOME/opt`
    1. `./autogen.sh`
    2. Add `#define FUSE_USE_VERSION 30` in `configure`, line 14861
    3. `CC=mpiicc CXX=mpiicpc ./configure --prefix=$HOME/opt --with-fuse-include=$HOME/opt/include/fuse3 --with-fuse-lib=$HOME/opt/lib64 --with-fuse-soname=fuse3`
    4. Add `-DFUSE_USE_VERSION=30` in `Makefile`, line 619
    5. make install
    6. `patchelf --add-rpath $HOME/opt/lib64 ../bin/squashfuse`
* squashfs-tools

## Convert to apptainer on the linux-cluster

```
apptainer build mypi.sif docker://sebwolf/mypi
mpirun -n 2 apptainer run --unsquash ./mypi.sif 10000
```

