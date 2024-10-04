import random
import string

def generate_random_text(length):
    """Gera um texto aleatório de tamanho `length`."""
    letters = string.ascii_lowercase + " "
    return ''.join(random.choice(letters) for _ in range(length))

def generate_substring_from_text(text, substring_length):
    """Gera uma substring que existe dentro do texto fornecido."""
    start_index = random.randint(0, len(text) - substring_length)
    return text[start_index:start_index + substring_length]

def generate_non_existing_substring(substring_length):
    """Gera uma substring aleatória que provavelmente não existe no texto."""
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for _ in range(substring_length))

def generate_test_cases(text_length, substring_length, num_cases=5):
    """Gera um texto e várias substrings existentes e não existentes."""
    text = generate_random_text(text_length)
    
    test_cases = []
    
    # Gera substrings existentes
    for _ in range(num_cases):
        substring = generate_substring_from_text(text, substring_length)
        test_cases.append((substring, True))
    
    # Gera substrings que não existem
    for _ in range(num_cases):
        substring = generate_non_existing_substring(substring_length)
        test_cases.append((substring, False))
    
    return text, test_cases

def save_to_file(text, test_cases, filename):
    """Salva o texto e os casos de teste em um arquivo no formato desejado."""
    substrings = []
    
    for substring, exists in test_cases:
        substrings.append(f'"{substring}"')
    
    # Salva no arquivo
    with open(filename, 'w') as f:
        f.write("Texto = [\n")
        f.write(f'"{text.strip()}"\n')
        f.write("]\n\n")
        
        f.write("Substrings = [\n")
        f.write(",\n".join(substrings))
        f.write("\n]\n")

# Exemplo de uso
if __name__ == "__main__":
    text_length = 100000        # Tamanho do texto grande
    substring_length = 100      # Tamanho das substrings a serem buscadas
    num_cases = 100             # Número de substrings a serem geradas

    text, test_cases = generate_test_cases(text_length, substring_length, num_cases)

    # Salva os casos de teste em um arquivo
    save_to_file(text, test_cases, "casos_de_teste.txt")

    print("Casos de teste salvos em 'casos_de_teste.txt'.")
