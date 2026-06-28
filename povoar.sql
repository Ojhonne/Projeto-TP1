-- ==========================================================
-- SCRIPT DE POVOAMENTO MASSIÇO DO BANCO DE DADOS (MS-BACKLOG)
-- ==========================================================

-- 1. INSERINDO PESSOAS
-- Domínio Senha: 6 chars, alternando letra/dígito (Ex: A1b2C3)
-- Domínio Papel: "DESENVOLVEDOR", "MESTRE SCRUM", "PROPRIETARIO DE PRODUTO"
INSERT INTO Pessoa (email, nome, senha, papel) VALUES 
('dono@teste.com', 'Joao', 'A1b2C3', 'PROPRIETARIO DE PRODUTO'),
('mestre1@teste.com', 'Carlos', ' A1b2C3', 'MESTRE SCRUM'),
('mestre2@teste.com', 'Ana', ' A1b2C3', 'MESTRE SCRUM'),
('dev1@teste.com', 'Lucas', ' A1b2C3', 'DESENVOLVEDOR'),
('dev2@teste.com', 'Mariana', ' A1b2C3', 'DESENVOLVEDOR'),
('dev3@teste.com', 'Pedro', ' A1b2C3', 'DESENVOLVEDOR'),
('dev4@teste.com', 'Julia', ' A1b2C3', 'DESENVOLVEDOR');


-- 2. INSERINDO PROJETOS
-- Domínio Codigo: LLDDD
INSERT INTO Projeto (codigo, nome, inicio, termino, scrum_master_email, product_owner_email) VALUES 
('PR001', 'Sistema Backlog', '10/01/2026', '20/12/2026', 'mestre1@teste.com', 'dono@teste.com'),
('PR002', 'App Mobile', '15/02/2026', '15/08/2026', 'mestre2@teste.com', 'dono@teste.com'),
('PR003', 'API de Pagamentos', '01/03/2026', '30/11/2026', 'mestre1@teste.com', 'dono@teste.com'),
('PR004', 'Portal Interno', '10/04/2026', '10/10/2026', 'mestre2@teste.com', 'dono@teste.com');


-- 3. INSERINDO PLANOS DE SPRINT
-- Domínio Codigo: LLDDD
INSERT INTO PlanoDeSprint (codigo, objetivo, capacidade, projeto_codigo) VALUES 
-- Sprints do Projeto 1
('SP001', 'Setup Inicial Backlog', '40', 'PR001'),
('SP002', 'Banco de Dados SQLite', '60', 'PR001'),
('SP003', 'Telas no Terminal', '50', 'PR001'),
-- Sprints do Projeto 2
('SP004', 'Prototipo UI App', '30', 'PR002'),
('SP005', 'Integracao com API', '80', 'PR002'),
-- Sprints do Projeto 3
('SP006', 'Gateway de Cartao', '100', 'PR003');


-- 4. INSERINDO HISTÓRIAS DE USUÁRIO
-- Restrição {OU}: Se tiver codigo_projeto, codigo_sprint deve ser NULL, e vice-versa.
-- Domínio Tempo (estimativa): 1 a 365
-- Domínio Estado: "A FAZER", "FAZENDO", "FEITO"
-- Domínio Prioridade: "ALTA", "MEDIA", "BAIXA"

-- ==========================================
-- PROJETO 1: Sistema Backlog
-- ==========================================
-- No Backlog (A FAZER, sem Sprint)
INSERT INTO HistoriaDeUsuario (codigo, titulo, papel, acao, valor, estimativa, prioridade, estado, codigo_projeto, codigo_sprint, pessoa_email) VALUES 
('HU001', 'Criar UI Login', 'Usuario', 'Logar no app', 'Acessar dados', '5', 'ALTA', 'A FAZER', 'PR001', NULL, NULL),
('HU002', 'Menu de Relatorios', 'Gerente', 'Ver graficos', 'Analisar avanco', '12', 'MEDIA', 'A FAZER', 'PR001', NULL, NULL);

-- Na Sprint 1 (Com desenvolvedores)
INSERT INTO HistoriaDeUsuario (codigo, titulo, papel, acao, valor, estimativa, prioridade, estado, codigo_projeto, codigo_sprint, pessoa_email) VALUES 
('HU003', 'Modelar Tabelas', 'DBA', 'Criar schema', 'Persistir dados', '3', 'ALTA', 'FEITO', NULL, 'SP001', 'dev1@teste.com'),
('HU004', 'CRUD Pessoas', 'Desenvolvedor', 'Cadastrar user', 'Ter acesso', '8', 'ALTA', 'FAZENDO', NULL, 'SP001', 'dev2@teste.com');

-- Na Sprint 2 (Com desenvolvedores)
INSERT INTO HistoriaDeUsuario (codigo, titulo, papel, acao, valor, estimativa, prioridade, estado, codigo_projeto, codigo_sprint, pessoa_email) VALUES 
('HU005', 'Conexao SQLite', 'Desenvolvedor', 'Abrir banco', 'Salvar dados', '6', 'ALTA', 'FAZENDO', NULL, 'SP002', 'dev3@teste.com'),
('HU006', 'Otimizar Query', 'DBA', 'Criar indices', 'Busca rapida', '4', 'MEDIA', 'A FAZER', NULL, 'SP002', 'dev1@teste.com');


-- ==========================================
-- PROJETO 2: App Mobile
-- ==========================================
-- No Backlog 
INSERT INTO  HistoriaDeUsuario (codigo, titulo, papel, acao, valor, estimativa, prioridade, estado, codigo_projeto, codigo_sprint, pessoa_email) VALUES 
('HU007', 'Tela de Perfil', 'Cliente', 'Ver meus dados', 'Atualizar foto', '7', 'MEDIA', 'A FAZER', 'PR002', NULL, NULL),
('HU008', 'Notificacoes Push', 'Usuario', 'Receber aviso', 'Nao perder info', '15', 'BAIXA', 'A FAZER', 'PR002', NULL, NULL);

-- Na Sprint 4
INSERT INTO  HistoriaDeUsuario (codigo, titulo, papel, acao, valor, estimativa, prioridade, estado, codigo_projeto, codigo_sprint, pessoa_email) VALUES 
('HU009', 'Navegacao Bottom', 'Cliente', 'Trocar de aba', 'Usabilidade', '5', 'ALTA', 'FEITO', NULL, 'SP004', 'dev4@teste.com'),
('HU010', 'Modo Escuro', 'Cliente', 'Mudar tema', 'Conforto visual', '10', 'MEDIA', 'FAZENDO', NULL, 'SP004', 'dev2@teste.com');


-- ==========================================
-- PROJETO 3: API de Pagamentos
-- ==========================================
-- Na Sprint 6
INSERT INTO HistoriaDeUsuario (codigo, titulo, papel, acao, valor, estimativa, prioridade, estado, codigo_projeto, codigo_sprint, pessoa_email) VALUES 
('HU011', 'Validar Cartao', 'Sistema', 'Checar num', 'Evitar fraude', '8', 'ALTA', 'FAZENDO', NULL, 'SP006', 'dev3@teste.com'),
('HU012', 'Gerar Recibo', 'Cliente', 'Baixar PDF', 'Comprovante', '6', 'MEDIA', 'A FAZER', NULL, 'SP006', NULL); -- Associado a sprint, mas sem dev ainda


-- ==========================================
-- PROJETO 4: Portal Interno (Projeto Novo, sem Sprints)
-- ==========================================
INSERT INTO HistoriaDeUsuario (codigo, titulo, papel, acao, valor, estimativa, prioridade, estado, codigo_projeto, codigo_sprint, pessoa_email) VALUES 
('HU013', 'Filtro de Busca', 'Funcionario', 'Achar docs', 'Ganhar tempo', '5', 'ALTA', 'A FAZER', 'PR004', NULL, NULL),
('HU014', 'Exportar Excel', 'Diretor', 'Gerar planilhas', 'Apresentar meta', '9', 'BAIXA', 'A FAZER', 'PR004', NULL, NULL);