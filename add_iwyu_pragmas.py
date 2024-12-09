import os
import sys

def add_iwyu_pragmas(directories):
    begin_pragma = '// IWYU pragma: begin_keep'
    end_pragma = '// IWYU pragma: end_keep'

    for directory in directories:
        for root, _, files in os.walk(directory):
            for file in files:
                file_path = os.path.join(root, file)
                if file_path.endswith(('.cpp', '.h', '.hpp', '.cc')):
                    try:
                        with open(file_path, 'r', encoding='utf-8') as f:
                            content = f.read()
                    except UnicodeDecodeError:
                        with open(file_path, 'r', encoding='latin-1') as f:
                            content = f.read()

                    if begin_pragma not in content and end_pragma not in content:
                        with open(file_path, 'w', encoding='utf-8') as f:
                            f.write(f'{begin_pragma}\n')
                            f.write(content)
                            f.write(f'\n{end_pragma}\n')

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python add_iwyu_pragmas.py <directory1> <directory2> ...")
        sys.exit(1)

    directories = sys.argv[1:]
    add_iwyu_pragmas(directories)
    print("IWYU pragmas added to all specific files 'keep' status")

