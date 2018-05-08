FROM mpi_base
MAINTAINER Edoarda <edvallim@gmail.com>

WORKDIR /home/lab/mpi/halflings

ADD . /home/lab/mpi/halflings
RUN chown -R lab:lab /home/lab/mpi/halflings
RUN chmod 755 /home/lab/mpi/halflings
USER lab