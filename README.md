# IrrigaPlantae

## Descrição
Sistema de Irrigação Automatizado utilizando IoT, desenvolvido como Trabalho de Conclusão de Curso (TCC) do curso de Análise e Desenvolvimento de Sistemas.

O projeto utiliza um microcontrolador ESP32 e um sensor de umidade do solo para monitorar as condições de irrigação em tempo real. Os dados coletados são disponibilizados por meio de uma interface web acessível via navegador, permitindo o acompanhamento da umidade de forma simples.

## Tecnologias Utilizadas
- ESP32
- Arduino IDE
- C++
- HTML
- CSS
- JavaScript
- WebSockets
- JSON
- LittleFS

## Funcionalidades
- Leitura da umidade do solo em tempo real
- Comunicação via WebSocket
- Interface web para monitoramento
- Armazenamento dos arquivos da interface utilizando LittleFS

## Créditos
Este projeto foi desenvolvido a partir de um exemplo disponibilizado por **Rui Santos e Sara Santos (Random Nerd Tutorials)**, posteriormente adaptado e expandido para atender aos objetivos do Trabalho de Conclusão de Curso.

Código de referência:
https://RandomNerdTutorials.com/esp32-websocket-server-sensor/

As principais modificações realizadas incluem:
- Adaptação para monitoramento de umidade do solo;
- Conversão das leituras para percentual de umidade;
- Personalização da interface web;
- Integração dos componentes utilizados no projeto IrriPlantae;
- Adequação da arquitetura para fins acadêmicos.

## Autora
**Gisele da Silva de Souza**

Trabalho de Conclusão de Curso – Análise e Desenvolvimento de Sistemas.
