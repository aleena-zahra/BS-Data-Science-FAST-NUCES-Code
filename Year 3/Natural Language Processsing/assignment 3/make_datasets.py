import json

def sample_json(input_path, output_path, line_limit=10000):
    """
    Reads the first 10000 lines of a file and writes them to a new file.
    This works best for JSON Lines (.jsonl) or large files where
    each record is on its own line.
    """
    try:
        with open(input_path, 'r', encoding='utf-8') as f_in:
            with open(output_path, 'w', encoding='utf-8') as f_out:
                for i, line in enumerate(f_in):
                    if i >= line_limit:
                        break
                    f_out.write(line)
        print(f"Successfully saved the first {line_limit} lines to {output_path}")
    except FileNotFoundError:
        print(f"Error: The file '{input_path}' was not found.")

# Example Usage
if __name__ == "__main__":
    sample_json('Beauty_5.json', 'beauty.json')
    sample_json('Electronics_5.json', 'electronics.json')
    sample_json('Home_and_Kitchen_5.json', 'home_and_kitchen.json')
    
