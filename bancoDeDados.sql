create table Estado(cod_estado int not null,
estado varchar(45) not null,
PRIMARY KEY(cod_estado)
);
create table Cidade(cod_cidade int not null,
cidade varchar(45) not null,
cod_estado int not null,
PRIMARY KEY(cod_cidade, cod_estado),
FOREIGN KEY(cod_estado) REFERENCES Estado(cod_estado)
);
create table Endereco(cod_endereco int not null,
cep int not null,
numero int not null,
rua varchar(45) not null,
bairro varchar(45) not null,
cidade varchar(45) not null,
cod_cidade int not null,
PRIMARY KEY(cod_endereco, cod_cidade),
FOREIGN KEY(cod_cidade) REFERENCES Cidade(cod_cidade)
);
create table Contato(cod_contato int not null,
nome varchar(45) not null,
PRIMARY KEY(cod_contato)
);
create table Email(
cod_email int not null,
enderecoemail varchar(45) not null,
cod_contato int not null,
PRIMARY KEY(cod_email, cod_contato),
FOREIGN KEY(cod_contato) REFERENCES Contato(cod_contato)
);
create table Telefone(
cod_telefone int not null,
telefone int not null,
cod_contato int not null,
PRIMARY KEY(cod_telefone, cod_contato),
FOREIGN KEY(cod_contato) REFERENCES Contato(cod_contato)
);
create table Contato_Endereco(
cod_contato int not null,
cod_endereco int not null,
PRIMARY KEY(cod_contato, cod_endereco),
FOREIGN KEY(cod_contato) REFERENCES Contato(cod_contato),
FOREIGN KEY(cod_endereco) REFERENCES Endereco(cod_endereco)
);
