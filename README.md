# Continente Barbosa do Bocage

Sistema de Controlo de Acesso
uPLC

## Entradas

I1 Espira ME P0 (Máquina Entrada) 

I2 Espira CH P-1 Presença Chamada P-1 para sair do parque (não residentes) (24V espira ocupada) 

I3 Espira CH P-2 Pulso Pulso 24V Chamada P-2 para sair do parque (residentes)

I4 Espira P0/P-1 (Descida) Pulso 24V detecção veículo a descer 

I5 Espira P0/P-1 (Subida) Pulso Pulso 24V detecção veículo a subir

I6 Espira P-1/P-2 (Descida) Pulso 24V detecção veículo a descer 

I7 Espira P-1/P-2 (Subida) Pulso Pulso 24V detecção veículo a subir

I8 Sinal Interfonia dos Residentes

I9 Estado Barreira P0 (Entrada) Estado Barreira (24V barreira aberta, 0V barreira fechada)

I10 Estado Barreira P-1 (Saída)Estado Barreira (24V barreira aberta, 0V barreira fechada)

I11 Estado Barreira P-1 (Auxiliar) Estado Barreira (24V barreira aberta, 0V barreira fechada)

I12 Sinal Leitor ME (Residentes) 24V Sinal validação Residente 

I13 Sinal Leitor ME/Interfonia Continente (Não Residentes) 24V Sinal validação Não Residente

I14 Estado Portão P0 (Entrada) Não Usado Estado Portão (24V Portão Fechado, 0V Aberto) 

I15 Estado Portão P-1 (Residentes) Não Usado Estado Portão (24V Portão Fechado, 0V Aberto)

### Outputs

O1 Sinal Ativação/Inibição Leitor ME (P0)  ON/OFF NF Leitor Ativado, NA Leitor desactivado

O2 Sinal Ativação/Inibição Leitor MS (P-1) ON/OFF NF Leitor Ativado, NA Leitor desactivado 

O3 Sinal Abrir Portão P0 (Entrada) PULSO Ordem Abrir Portão. Contacto NF abrir portão

O4 Sinal Abrir Portão P-1 (Residentes) PULSO Ordem Abrir Portão. Contacto NF abrir portão 

O5 Sinal Abrir Barreira P0 PULSO Ordem Abrir Barreira (apenas durante a saída). Contacto NF abrir portão

O6 Sinal Abrir Barreira P-1 (Auxiliar) PULSO Ordem Abrir Barreira. Contacto NF abrir portão




## Authors

* **Luís Tavares** - Soltráfego

.
