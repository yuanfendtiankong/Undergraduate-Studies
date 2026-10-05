param([string]$File = '0001_two_sum.cpp')

$ErrorActionPreference = 'Stop'
if ([System.IO.Path]::IsPathRooted($File)) {
    $sourcePath = (Resolve-Path -LiteralPath $File).Path
} else {
    $sourcePath = (Resolve-Path -LiteralPath (Join-Path $PSScriptRoot $File)).Path
}
if ([System.IO.Path]::GetExtension($sourcePath) -ne '.cpp') {
    throw 'Choose a .cpp source file.'
}
$compilerPath = (Get-Command g++ -CommandType Application -ErrorAction Stop).Source
$buildPath = Join-Path $PSScriptRoot '.build'
New-Item -ItemType Directory -Path $buildPath -Force | Out-Null
$executablePath = Join-Path $buildPath ([System.IO.Path]::GetFileNameWithoutExtension($sourcePath) + '.exe')

& $compilerPath '-std=c++17' '-g' '-O0' '-Wall' '-Wextra' '-DLOCAL' $sourcePath '-o' $executablePath
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
& $executablePath
exit $LASTEXITCODE
