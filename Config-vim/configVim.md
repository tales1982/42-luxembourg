configurando o vim

pluguins para estalar no vim

🔗 Vim Airline: https://github.com/vim-airline/vim-ai...
🔗 NERDTree: https://github.com/preservim/nerdtree
🔗 Surround.vim: https://github.com/tpope/vim-surround
🔗 Auto-pairs: https://github.com/jiangmiao/auto-pairs
🔗 Vim Auto Markdown: https://github.com/terroo/vim-auto-ma...
🔗 Tabnine: https://bit.ly/2BpEUHG   
 Vim Instant Markdown: LINK
 
 Instale o Vim-Plug:
O Vim Airline é um plugin para o Vim que melhora a barra de status, 
fornecendo informações visuais úteis enquanto você trabalha no editor Vim

=============== 1° Abra um terminal e digite:
    curl -fLo ~/.vim/autoload/plug.vim --create-dirs \
    https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
    
     Configure seu arquivo .vimrc:
     Abra ou crie o arquivo ~/.vimrc (ou vim touch ~/.vimrc no terminal) e adicione as seguintes linhas:

" Vim-Plug setup
call plug#begin('~/.vim/plugged')

" Add Vim Airline
Plug 'vim-airline/vim-airline'

" Instale os plugins e carregue-os automaticamente
call plug#end()

" Ative o Vim Airline
set laststatus=2

depois :PlugInstall para estalar fassa isso pra os outros pluguins

=============== 2° NERDTree
 é outro plugin muito popular para o Vim que adiciona uma estrutura de árvore de
 diretórios ao lado da janela do editor. Ele serve para facilitar a navegação e a manipulação
  de arquivos e diretórios no seu sistema de arquivos enquanto você está trabalhando no Vim.
  
  " Add NERDTree
Plug 'preservim/nerdtree'

=============== 3° O plugin Surround.vim 
é uma ferramenta poderosa para facilitar a manipulação de delimitadores, como parênteses, colchetes, aspas e tags HTML,
 no Vim. Ele oferece funcionalidades para adicionar, alterar ou remover esses delimitadores de maneira eficiente e rápida.

" Add Surround.vim
Plug 'tpope/vim-surround'
 
 =============== 4° O Auto-pairs é um plugin para o Vim que automatiza o fechamento de pares de 
 caracteres (como parênteses, colchetes, chaves, aspas etc.) 
 
 " Add Auto-pairs
Plug 'jiangmiao/auto-pairs'
 
 =============== 5°O Vim Auto Markdown 
 é um plugin para o Vim que facilita a escrita e formatação de documentos no formato Markdown. 
 Ele oferece recursos automatizados para ajudar na edição de textos nesse formato, 
 fornecendo atalhos e facilidades para tarefas comuns, como inserção de cabeçalhos, 
 listas, enfatização de texto e muito mais
 
 " Add Vim-AutoMarkdown
Plug 'godlygeek/tabular'
Plug 'plasticboy/vim-markdown'
 
 
 =============== 6° 
O Tabnine é uma extensão ou plugin de autocompletar inteligente que oferece sugestões de código
 altamente precisas e personalizadas enquanto você está programando. Ele utiliza técnicas avançadas
  de aprendizado de máquina para entender o contexto do código que está sendo escrito e oferecer 
  sugestões relevantes em tempo real.

curl -fLo ~/.vim/autoload/plug.vim --create-dirs \
   https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim


Digite o seguinte comando para instalar o TabNine:
curl -sSL https://install.tabnine.com | sh

Adicione as seguintes linhas ao arquivo .vimrc:
" Habilitar o TabNine
let g:deoplete#enable_at_startup = 1
let g:deoplete#sources#tabnine#enabled = 1

 
 =============== 7°O Vim Instant Markdown 
 é um plugin para o Vim que permite visualizar a renderização imediata de arquivos Markdown 
 enquanto você os edita. Ele facilita a edição e a visualização rápida de arquivos Markdown, 
 
curl -fLo ~/.vim/autoload/plug.vim --create-dirs \
   https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
   
   
 
 ======================= outros para estalar
 "-------------YOUCOMPLETEME---------------
"
let g:ycm_global_ycm_extra_conf = '~/.vim/.ycm_extra_conf.py'
set completeopt-=preview
let g:ycm_show_diagnostics_ui = 0
"-------------FIM YOUCOMPLETEME --------

"ativa indentação inteligente, o Vim tentará adivinhar
" qual é a melhor indentação para o código quando você
" efetuar quebra de linha. Funciona bem para linguagem C
set smartindent
 
 " por padrão o vim armazena os últimos 50 comandos que você
" digitou em seu histórico. Eu sou exagerado, prefiro armazenar
" os últimos 5000
set history=5000
 
 
 " ativar numeração de linha
set number
set title

"Para pergunta se quero salva ao sai
set confirm 
" destaca a linha em que o cursor está posicionado
" ótimo para quem não enxerga muito bem
set cursorline

" ativa o clique do mouse para navegação pelos documentos
set mouse=a
 
 " ativa o compartilhamento de área de transferência entre o Vim
" e a interface gráfica
set clipboard=unnamedplus

" converte o tab em espaços em branco
" ao teclar tab o Vim irá substutuir por 2 espaços
set tabstop=2 softtabstop=2 expandtab shiftwidth=2

" ao teclar a barra de espaço no modo normal, o Vim
" irá colapsar ou expandir o bloco de código do cursor
" foldlevel é a partir de que nível de indentação o 
" código iniciará colapsado
set foldmethod=syntax
set foldlevel=99
nnoremap <space> za


let g:indentLine_enabled = 1
map <C-k>i :IndentLinesToggle<CR>
map q :quit<CR>
map <C-q> :quit!<CR>
map <C-s> :write<CR>
map <C-n> :NERDTreeToggle<CR>
set encoding=utf8
set guifont=Anonymice\ Nerd\ Font\ Mono:h12
"o set incsearch serve pra fazer uma preocura por nomes use o /e oque quero
"preocura
set incsearch
" O wildmenu me mostra uma aba com os nomes do arquivos que estou preocurando
set wildmenu
 
 " ativar sintaxe colorida
syntax on
 
 
 
 
 
 
 
 
 
 
 
 
