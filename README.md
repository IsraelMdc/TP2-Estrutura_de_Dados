# Simulação de Realização de Exames de Raio-X (parte 2)

  Este trabalho prático consiste em simular o processo de realização de exames de raio-X de tórax em um hospital, com ênfase na organização da fila para laudo médico. 

## Estrutura do Projeto

O projeto contem os seguintes arquivos:

- **patient.h**
  - Declarações das funções para gerenciar e manipular os pacientes.

- **patient.c**
  - Implementação das funções para gerenciar e manipular os pacientes.

- **exam.h**
  - Declarações das funções para gerenciar e manipular os exames.

- **exam.c**
  - Implementação das funções para gerenciar e manipular os exames.
 
- **machine.h**
  - Declarações das funções para gerenciar e manipular as maquinas de raio-x.

- **machine.c**
  - Implementação das funções para gerenciar e manipular as maquinas de raio-x.
 
- **report.h**
  - Declarações das funções para gerenciar e manipular os laudos.

- **report.c**
  - Implementação das funções para gerenciar e manipular os laudos.
    
- **Makefile**
  - Arquivo para execução do projeto.
  

## Principais TADs (Tipos Abstratos de Dados)

### Existem 4 TADs principais no projeto, sendo eles:

#### Patient
O TAD `Patient` representa um paciente e contém:

- `int id`: Identificador único do paciente.
- `char* name`: Nome do paciente.
- `timestamp`: Horário de chegada do paciente no hospital.
  
#### Exam

O TAD `Exam` representa um exame e contém:

- `int id`: Identificador único do exame.
- `int patient_id`: Identificador do paciente associado ao exame.
- `int machine_id`: Identificador do aparelho de raio-x associado ao exame
- `char condition_IA`: Condição do paciente dada pela IA: 
- `int timestamp`: Horario de começo do exame.
- - `int gravidade`: Nivel de gravidade da condição dada pela IA.

#### Machine
O TAD `Machine` representa uma máquina de raio-x e contém:

- `int id_machine`: Identificador único da máquina.
- `int is_occupied;`: determina se a maquina está disponivel ou não.
- `int machine_timestamp`: horário de chegada na máquina pelo paciente.
- `Patient *machine_patient`: Ponteiro para os dados do paciente.

#### Report
O TAD `Report` representa um laudo e contém:

- `int id`: Identificador único do exame.
- `int exam_id`: Identificador do exame de base do laudo.
- `char condition_IA`: Condição do paciente dada pela IA, depois de ser revisada pelo médico;
- `int timestamp`: horário de término do laudo.




## Como Executar e Utilizar o Projeto

Para compilar e executar o projeto, siga o passo abaixo:
1. Execute o arquivo Makefile usando o comando "make" em linux ou "mingw32-make" em windows.
