# Script that synchronizes the local test data

$TestsInputDirectory = "tests\input"
$TestSet = "public"
$TestFiles = "CMD.EXE-087B4001.pf PING.EXE-B29F6629.pf TASKHOST.EXE-3AE259FC.pf WUAUCLT.EXE-830BCC14.pf"

If (-Not (Test-Path ${TestsInputDirectory}))
{
	New-Item -Name ${TestsInputDirectory} -ItemType "directory" | Out-Null
}
If (-Not (Test-Path "${TestsInputDirectory}\${TestSet}"))
{
	New-Item -Name "${TestsInputDirectory}\${TestSet}" -ItemType "directory" | Out-Null
}
ForEach ($TestFile in ${TestFiles} -split " ")
{
	$UrlTestFile = [System.Uri]::EscapeDataString("${TestFile}")
	$Url = "https://raw.githubusercontent.com/log2timeline/plaso/refs/heads/main/test_data/winprefetch/${UrlTestFile}"

	$ProgressPreference = 'SilentlyContinue'
	Invoke-WebRequest -Uri ${Url} -OutFile "${TestsInputDirectory}\${TestSet}\${TestFile}"
}
