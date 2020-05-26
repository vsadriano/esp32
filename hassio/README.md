# Instalação do Home Assitant (Hass.io)

Frente ao movimento de descontinuidade, foi editado e versionado esse script, de forma a auxiliar os usuários que ainda utilizam essa plataforma.

## Processo de instalação

### Plataformas Suportadas

- intel-nuc
- odroid-c2
- odroid-n2
- odroid-xu
- qemuarm
- qemuarm-64
- qemux86
- qemux86-64
- raspberrypi
- raspberrypi2
- raspberrypi3
- raspberrypi4
- raspberrypi3-64
- raspberrypi4-64
- tinker

### Script de instalação

Para iniciar o instalador, executar o comando:

```shell
MACHINE=$PLATAFORMA curl -sL https://github.com/vsadriano/esp32/hassio/install.sh | bash -s
```

> Para dar continuidade ao processo, digitar "not supported", frente à mensagem de warning.
