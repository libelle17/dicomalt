set number
set autoindent
set tabstop=2
set autoread
set history=700
" filetype plugin on
" filetype indent on
set autoread
set so=3
set wildmenu
set wildmode=longest:full,full
set ruler
set cmdheight=2
set backspace=eol,start,indent
set whichwrap+=<,>,h,l
set ignorecase
set hlsearch
" set incsearch
set magic
set showmatch
set mat=2
set noerrorbells
set visualbell
set t_vb=
set tm=500
syntax enable
" colorscheme desert
" set background=dark
set encoding=utf8
set ffs=unix,dos,mac
set noexpandtab
set smarttab
set shiftwidth=2
set lbr
set tw=1000
" set ai
" set si
set wrap
set laststatus=2
set mouse=a
nnoremap <silent><C-j> m`:silent +g/\m^\s*$/d<CR>``:noh<CR>
nnoremap <silent><C-k> m`:silent -g/\m^\s*$/d<CR>``:noh<CR>
nnoremap <silent><A-j> :set paste<CR>m`o<Esc>``:set nopaste<CR>
nnoremap <silent><A-k> :set paste<CR>m`O<Esc>``:set nopaste<CR>

inoremap <c-c> <c-o>:set nocul<cr><c-c>
:au InsertEnter * set cul
" :au InsertEnter *  hi StatusLine term=reverse ctermbg=5 gui=undercurl guisp=Magenta
:au InsertLeave * set nocul
" :au InsertLeave *  hi StatusLine term=reverse ctermfg=0 ctermbg=7 gui=bold,reverse
set tabpagemax=100
nnoremap t <C-]>
" nmap \\ <c-]>
nnoremap <C-j> :cclose<CR>
nnoremap <C-T> :GtagsCursor<CR>
map <C-n> :cn<CR>
map <C-p> :cp<CR>
map <C-k> :Gtags-cscope<CR><CR> 
command -nargs=* Make make stumm | cwindow 3
command -nargs=* Meike make <args> | cwindow 3
inoremap <C-w> <ESC>:wa<CR>
nnoremap <C-w> :wa<CR>
map <Leader>0 <C-w>:Make<CR>
map <Leader>ß :Meike stumminst<CR>
map <Leader>? :make git<CR>
autocmd QuickFixCmdPost [^l]* nested cwindow
autocmd QuickFixCmdPost    l* nested lwindow
