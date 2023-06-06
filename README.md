# ./minishell #

## --- MAN ---
#### -> prototypes
Functions **without** ```ft_``` are main commands and **with** ```ft_``` are utils functions</br>
 --- Like ```prompt_launch``` and ```ft_strlen```</br></br>

#### -> algo
Main is calling simple ```void``` functions with the ```t_data``` struct where all data is stored</br></br>

#### -> global
There is one global variable named ```g_data_access``` who point on t_data struct</br>
Not used yet but may be util for the signal handling</br></br>

#### -> parsing
The command send by the user is stored in the ```char **command``` where each row contains separate instructions</br> 
 --- So ```echo '$USER' <<<  ouistiti | cat "/home/file.pdf" ```</br>
 --- Is ```echo``` ```acrespy``` ```<<<``` ```|``` ```cat``` ```/home/file.pdf```</br></br>

#### -> env
You can modify the environement with (data, name (without =), value)</br>
 --- ```env_update```</br>
 --- ```env_add```</br>
 --- ```env_delete```</br>

## --- TODO ---
#### -> malloc unprotected
```ft_env_size```</br>
```ft_itoa```</br>
```ft_strjoin```</br></br>

#### -> signals
When ```SIGQUIT``` received showing cursor before ```minishell>``` but writing on the right pos</br>
Sometimes ```SIGQUIT``` writes ```minishell>``` after ```minishell>```</br>

#### -> norm
Fix ```ft_dollar_replace``` and ```ft_dollar_check``` +4 args +25 lines</br>
Correct all errors that I leave because I didn't install the Norminette</br></br>

#### -> leaks
Make ```signal_handle``` call ```ft_free``` when ctrl+d is received