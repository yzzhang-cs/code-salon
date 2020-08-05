import cpp_stylist as cpps
import argparse
import sys
import re
import os

parser = argparse.ArgumentParser(description='Style the source code.')
parser.add_argument('input_file', help='the input source code')
parser.add_argument('output_file', help='the output source code')
parser.add_argument('--lang', help='the language of the source code', default='cpp')
parser.add_argument('--new-line', help='if you want new line before parentheses, default is false', default=False)
parser.add_argument('--delete-empty-lines', help='if you want to delete the empty lines, default is false', default=False)
args = parser.parse_args()

non_escaped_double_quotes = re.compile(r"(?<!\\)\"")
non_line_tail_semi_colons = re.compile(";[^\\n]")
multi_line_comment = re.compile("\\/\\*|\\*\\/")
single_line_comment = re.compile(r"//")
#string_regex = re.compile(r'/"(?:[^"\\]|\\.)*"/')
string_regex = re.compile(r'.+')

def str_to_bool(s):
	if(not s):
		return False;
	s = s.lower()
	if(s == 'true' or s == '1'):
		return True
	else:
		return False # default is false
		
delete_empty_lines = str_to_bool(args.delete_empty_lines)

def construct_option_string():
	s = ""
	if(str_to_bool(args.new_line)):
		s += 'new_line=' + '1'
	else:
		s += 'new_line=' + '0'
	return s
	
def toggle(flag):
	return not flag
	
def add_new_lines_after_semi_colons(s):
	result = ""
	lines = non_line_tail_semi_colons.split(s)
	for line in lines:
		result += line + ';' + '\n'
	return result
	
def process_line(line):
	result = ""
	words = line.split()
	if(len(words) > 0):
		result += words[0]
		for word in words[1:]:
			if(word != '{' and word != '}'):
				result += ' ' + word
			else:
				result += word
	if(line.endswith(';')):
		result += '\n'
	return result
	
def process_non_string(s):
	result = ""
	lines = s.split('\n')
	for line in lines:
		if(line.startswith('#') or single_line_comment.search(line)): # lines starts with '#', like #include ..., we just copy it
			result += line.strip() + '\n'
		elif(line.strip() == ''): # empty line
			result += '\n'
		else:
			result += process_line(line)
	return result
	
# process the source code line-by-line to clean the code
def get_clean_string(source):
	result = ""
	in_comment = False
	
	comment_slices = multi_line_comment.split(source)
	for comment_slice in comment_slices:
		if(not in_comment):
			in_string = False
			string_slices = non_escaped_double_quotes.split(comment_slice)
			
			for slice in string_slices:
				if(not in_string):
					result += process_non_string(slice)
					in_string = not in_string
				else:
					result += ' "'
					result += slice
					result += '" '
					in_string = not in_string
			in_comment = not in_comment
		else:
			result += '/*'
			result += comment_slice
			result += '*/'
			in_comment = not in_comment
			
	return result

def main():
	in_file = open(args.input_file)
	
	if os.path.dirname(args.output_file) != '':
		os.makedirs(os.path.dirname(args.output_file), exist_ok=True)
	out_file = open(args.output_file, 'w+')
	
	stylist = cpps.CppStylist(construct_option_string())
	
	source = in_file.read()
	cleaned_source = get_clean_string(source)
	#print(cleaned_source)
	styled = stylist.style(cleaned_source)
	
	out_file.write(styled)
	
	
	

if __name__ == "__main__":
	main()