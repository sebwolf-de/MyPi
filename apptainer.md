# Apptainer on the linux-cluster

## Build docker container locally and push to dockerhub

```
docker build -f Dockerfile -t sebwolf/mypi:latest
docker push sebwolf/mypi
```

## Convert to apptainer on the linux-cluster

```
apptainer build --sandbox sandbox docker://sebwolf/mypi
srun apptainer run sandbox 100
```

