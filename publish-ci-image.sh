#!/usr/bin/env bash
# Builds the CI image, pushes it to ghcr.io, and updates the image tag in
# main.yml. Run this after editing the Dockerfile and verifying with
# run-local-ci.sh.
#
# Usage: GHRCIO_TOKEN=<token> ./publish-ci-image.sh
set -euo pipefail

: "${GHRCIO_TOKEN:?GHRCIO_TOKEN is not set}"

REGISTRY="ghcr.io"
REPO="mitchellthompkins/gcem"
IMAGE="${REGISTRY}/${REPO}/ci"
WORKFLOW=".github/workflows/main.yml"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

TAG="$(sha256sum Dockerfile | cut -c1-12)"
echo "Tag: $TAG"

echo "Building ${IMAGE}:${TAG} ..."
docker build -t "${IMAGE}:${TAG}" .

echo "Logging in to ${REGISTRY} ..."
echo "${GHRCIO_TOKEN}" | docker login "${REGISTRY}" -u MitchellThompkins --password-stdin

echo "Pushing ${IMAGE}:${TAG} ..."
docker push "${IMAGE}:${TAG}"

echo "Updating $WORKFLOW ..."
sed -i "s|${IMAGE}:[^[:space:]]*|${IMAGE}:${TAG}|g" "$WORKFLOW"

echo "Done. Commit Dockerfile and $WORKFLOW together."
