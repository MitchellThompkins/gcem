# Contributing

## Running CI Locally

Build the CI image:

```bash
docker build -t gcem/ci:latest .
```

Run the full compiler matrix against your local changes:

```bash
./run-local-ci.sh
```

## Updating the CI Image

After editing the Dockerfile, verify it locally with the steps above, then publish:

```bash
GHRCIO_TOKEN=<token> ./publish-ci-image.sh
```

This builds the image, pushes it to the registry tagged with the Dockerfile's
content hash, and updates the tag in `.github/workflows/main.yml`. Commit the
Dockerfile and the updated `main.yml` together.
