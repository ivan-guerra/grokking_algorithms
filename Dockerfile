# This Dockerfile will build an Alpine Linux image which includes the compiled
# source for each of the GA chapters. You can edit the code in your local
# checkout, rebuild the docker image, and launch a container instance to see
# your changes take effect.

# This Dockerfile uses a multi-stage build. The first stage, builder, builds
# the GA samples/exercises. The second stage copies the binaries from builder
# to the final image.

FROM alpine:latest AS builder

# Install all the packages needed to build GA sample/exercise code.
RUN apk add --no-cache \
        build-base     \
        cmake          \
        bash

# Copy the grokking_algorithms source tree.
COPY ./ /grokking_algorithms/

# Build GA code using the build script included in the source tree.
WORKDIR /grokking_algorithms/scripts
RUN chmod +x build.sh && \
    ./build.sh

FROM alpine:latest

# Install all packages needed to run the samples and bash so you can
# launch a container with a bash shell if its preferred over regular sh.
RUN apk add --no-cache \
        bash           \
        libgcc         \
        libstdc++

# Copy the binaries from the builder image to this final image.
COPY --from=builder /grokking_algorithms/bin/ /examples/

WORKDIR /examples
