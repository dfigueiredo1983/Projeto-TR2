import sqlite3

def create_dataBase(nome_banco, nome_tabela):
    try:
        conexao = sqlite3.connect(nome_banco)
        cursor = conexao.cursor()
        try:
            cursor.execute(f'''
                CREATE TABLE IF NOT EXISTS {nome_tabela} (
                        id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
                        medida TEXT NOT NULL,
                        data TEXT NOT NULL,
                        hora TEXT NOT NULL
                    );
            ''')
            conexao.commit()
        except Exception as erro:
            print(f"Erro ao criar a tabela {nome_tabela} - {erro}")

        conexao.close()
    except:
        print(f"Erro ao criar o banco: '{nome_banco}'")