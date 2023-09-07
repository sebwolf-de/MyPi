# Apptainer on the linux-cluster

## Build docker container locally and push to dockerhub

```
docker build -f Dockerfile -t sebwolf/mypi:latest
docker push sebwolf/mypi
```

## Install a lot of stuff on the linux-cluster manually
* ninja
* meson
* Fuse
* squashfuse (needs patching for `-DFUSE_USE_VERSION=30`, also need to add correct rpath with patchelf)
* squashfs-tools

## Convert to apptainer on the linux-cluster

```
apptainer build mypi.sif docker://sebwolf/mypi
mpirun -n 2 apptainer run --unsquash ./mypi.sif 10000
```

