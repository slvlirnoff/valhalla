FROM ubuntu:16.04
MAINTAINER Grant Heffernan <grant@mapzen.com>

ENV TERM vt100

ENV DATA_DIR ${DATA_DIR:-"/data/valhalla"}
ENV CONF_FILE ${CONF_FILE:-"/conf/valhalla.json"}

RUN apt-get update -y
RUN apt-get install \
      wget \
      osmosis \
      osmctools \
      pigz \
      parallel \
      awscli \
      supervisor \
      software-properties-common \
      -y

ADD ./scripts/install_dependencies.sh /scripts/install_dependencies.sh

RUN /scripts/install_dependencies.sh


ADD ./integration_key /integration_key
ADD ./ssh_config /root/.ssh/config


RUN apt-get install openssh-client -y

RUN chmod 0600 ./integration_key; \
    eval "$(ssh-agent -s)" && ssh-add ../integration_key;

RUN ssh -l git gitlab.intern.routerank.com

ADD ./scripts/ /scripts/
RUN /scripts/install_from_source.sh

RUN rm ../integration_key; \
    rm ~/.ssh/config

ADD ./conf /conf

RUN valhalla_build_config \
      --mjolnir-tile-dir ${DATA_DIR}/tiles \
      >${CONF_FILE}

RUN apt-get clean && \
  rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

ADD ./start_valhalla.sh .
ADD ./valhalla_scripts /valhalla_scripts

EXPOSE 8002
CMD ["/start_valhalla.sh"]