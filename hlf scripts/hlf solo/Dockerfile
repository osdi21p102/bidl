From ubuntu
ADD . /root/FabricClient

RUN cd \
    && apt update \
    && apt install build-essential curl vim python3 python -y \
    && curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.35.3/install.sh | bash \
    && export NVM_DIR="$HOME/.nvm" \
    && [ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"  \
    && [ -s "$NVM_DIR/bash_completion" ] && \. "$NVM_DIR/bash_completion" \
    && nvm install v8.9.4 \
    && cd FabricClient && npm install

WORKDIR /root/FabricClient
