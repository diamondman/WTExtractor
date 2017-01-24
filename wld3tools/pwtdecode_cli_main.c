#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "pwt_decode.h"
#include "dataaccessors.h"
//#include <argp.h>

int main(int args, char** argv){
  if(args == 1){
    printf("Missing file path.\n");
    return 1;
  }

  DataAccessor* acc = openFileAccessor(argv[1]);
  PWT* pwt = pwt_extract(acc);

  if(pwt){
    //pwt_print(pwt);
    pwt_free(pwt);
  }else
    printf("ERROR! DONE!\n");

  if(acc){
      printf("OFFSET: %zu; Len %zu\n", ftell(acc->dat.file), acc->length);
      freeFileAccessor(acc);
  }

  return 0;
}


//const char *argp_program_version =
//  "WTextract 0.0.0alpha";
//const char *argp_program_bug_address =
//  "<jessy,diamondman@gmail.com>";
//
///* Program documentation. */
//static char doc[] = "Extract WLD3 files.";
//
///* A description of the arguments we accept. */
//static char args_doc[] = "infile outfile";
//
///* The options we understand. */
//static struct argp_option options[] = {
//  {"verbose",  'v', 0,      0,  "Produce verbose output" },
//  {"quiet",    'q', 0,      0,  "Don't produce any output" },
//  {"silent",   's', 0,      OPTION_ALIAS },
//  {"output",   'o', "FILE", 0,
//   "Output to FILE instead of standard output" },
//  { 0 }
//};
//
///* Used by main to communicate with parse_opt. */
//struct arguments{
//  char *args[2];                /* arg1 & arg2 */
//  int silent, verbose;
//  char *output_file;
//};
//
///* Parse a single option. */
//static error_t parse_opt (int key, char *arg, struct argp_state *state){
//  /* Get the input argument from argp_parse, which we
//     know is a pointer to our arguments structure. */
//  struct arguments *arguments = state->input;
//
//  switch (key)
//    {
//    case 'q': case 's':
//      arguments->silent = 1;
//      break;
//    case 'v':
//      arguments->verbose = 1;
//      break;
//    case 'o':
//      arguments->output_file = arg;
//      break;
//
//    case ARGP_KEY_ARG:
//      if (state->arg_num >= 2)
//	/* Too many arguments. */
//	argp_usage (state);
//
//      arguments->args[state->arg_num] = arg;
//
//      break;
//
//    case ARGP_KEY_END:
//      if (state->arg_num < 2)
//	/* Not enough arguments. */
//	argp_usage (state);
//      break;
//
//    default:
//      return ARGP_ERR_UNKNOWN;
//    }
//  return 0;
//}
//
///* Our argp parser. */
//static struct argp argp = { options, parse_opt, args_doc, doc };
//
//int main (int argc, char **argv){
//  struct arguments arguments;
//
//  /* Default values. */
//  arguments.silent = 0;
//  arguments.verbose = 0;
//  arguments.output_file = "-";
//
//  /* Parse our arguments; every option seen by parse_opt will
//     be reflected in arguments. */
//  argp_parse (&argp, argc, argv, 0, 0, &arguments);
//
//  printf ("ARG1 = %s\nARG2 = %s\nOUTPUT_FILE = %s\n"
//	  "VERBOSE = %s\nSILENT = %s\n",
//	  arguments.args[0], arguments.args[1],
//	  arguments.output_file,
//	  arguments.verbose ? "yes" : "no",
//	  arguments.silent ? "yes" : "no");
//
//  exit (0);
//}
