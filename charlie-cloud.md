# Charliecloud on the linux-cluster

## Build docker container locally and push to dockerhub

```
docker build -f Dockerfile -t sebwolf/mypi:latest
docker push sebwolf/mypi
```

## Run charliecloud on the linux cluster

Build on the linux cluster.
```
ch-image build -t mypi -f Dockerfile . --force
ch-convert mypi ./ch-image
```

Run without MPI on the login node:
```
ch-run -u 0 -w -b /gpfs:/gpfs -b /dss:/dss -b /lrz:/lrz -t -c $(pwd) ./ch-image -- /usr/mypi/build/mypi 10000
```

Run with MPI on two compute nodes:
```
mpiexec -n 112 ch-run -u 0 -w -b /gpfs:/gpfs -b /dss:/dss -b /lrz:/lrz -t -c $(pwd) ./ch-image -- /usr/mypi/build/mypi 1120000
```

The container has access to the filesystem:
```
ch-run -u 0 -w -b /gpfs:/gpfs -b /dss:/dss -b /lrz:/lrz -t -c $(pwd) ./ch-image -- cat Dockerfile
```
