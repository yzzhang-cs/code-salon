import cpp_stylist as cpps
import argparse
import sys
import re

parser = argparse.ArgumentParser(description='Style the source code.')
parser.add_argument('input_file', help='the input source code')
parser.add_argument('output_file', help='the output source code')
parser.add_argument('--lang', help='the language of the source code', default='cpp')
parser.add_argument('--new-line', type=bool, help='if you want new line before parentheses', default=False)
args = parser.parse_args()

non_escaped_double_quotes = re.compile("[^\\\]\"")
non_line_tail_semi_colons = re.compile(";[^\\n]")
	
def construct_option_string():
	s = ""
	if(args.new_line):
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
	return result
	
def process_non_string(s):
	result = ""
	lines = s.split('\n')
	for line in lines:
		if(line.startswith('#') or line.startswith('//')): # lines starts with '#', like #include ..., we just copy it
			result += line + '\n'
		elif(line == '\n'): # empty line
			result += '\n'
		else:
			result += process_line(line)
	return result
	
# process the source code line-by-line to clean the code
def get_clean_string(source):
	result = ""
	in_string = False
	
	slices = non_escaped_double_quotes.split(source)
	for slice in slices:
		if(not in_string):
			result += process_non_string(slice)
			in_string = toggle(in_string)
		else:
			result += '\"'
			result += slice
			result += '\"'
			in_string = toggle(in_string)
		result += ' '
	return result

def main():
	in_file = open(args.input_file)
	out_file = open(args.output_file, 'w')
	
	stylist = cpps.CppStylist(construct_option_string())
	
	source = in_file.read()
	cleaned_source = get_clean_string(source)
	styled = stylist.style(cleaned_source)
	
	out_file.write(styled)
	
	
	

if __name__ == "__main__":
	main()