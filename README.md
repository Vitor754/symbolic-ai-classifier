# Engine de Classificação Simbólica de IA

## Contexto
Desenvolvido como parte do curso **Algoritmos e Estruturas de Dados II (CES-11)** do **Instituto Tecnológico de Aeronáutica (ITA)**.

## Objetivo
O objetivo era construir um **Sistema de Aprendizagem Simbólica** (um classificador baseado em regras) capaz de se auto-otimizar. Diferentemente de algoritmos estáticos, este motor simula um fluxo de trabalho básico de Aprendizado de Máquina, recebendo feedback sobre suas previsões e ajustando dinamicamente a "confiança" (peso) de suas regras.

## Destaques Técnicos
* **Estrutura de Dados:** Implementada uma **Heap Binária Máxima** para gerenciar as regras de classificação. Isso garante acesso $O(1)$ à regra de maior prioridade, tornando o processo de decisão extremamente rápido.

* **Lógica Adaptativa:** O sistema implementa um loop de feedback:
* **Recompensa:** Previsões corretas aumentam o peso da regra (+0,5).
* **Penalidade:** Previsões incorretas diminuem o peso da regra (-0,3).
* **Resolução de Conflitos:** Lida com dados ambíguos seguindo rigorosamente a hierarquia de prioridades mantida pelo Heap.

## Operações Principais
* **ADDREGRA:** Insere uma nova regra na base de conhecimento com um peso específico.
* **CLASSIFICAR:** Compara os dados de entrada com o conjunto de regras para prever uma classe (por exemplo, Alta, Média, Baixa).
* **APRENDER:** Ajusta automaticamente os pesos internos com base no sucesso ou falha da classificação.
