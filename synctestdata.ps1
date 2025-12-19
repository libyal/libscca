# Script that synchronizes the local test data
#
# Version: 20251217

$Repository = "log2timeline/plaso"
$TestDataPath = "test_data/winprefetch"
$TestSet = "public"
$TestInputDirectory = "tests/input"
$TestFiles = "CMD.EXE-087B4001.pf PING.EXE-B29F6629.pf TASKHOST.EXE-3AE259FC.pf WUAUCLT.EXE-830BCC14.pf"

If (-Not (Test-Path ${TestInputDirectory}))
{
	New-Item -Name ${TestInputDirectory} -ItemType "directory" | Out-Null
}
If (-Not (Test-Path "${TestInputDirectory}\${TestSet}"))
{
	New-Item -Name "${TestInputDirectory}\${TestSet}" -ItemType "directory" | Out-Null
}
ForEach ($TestFile in ${TestFiles} -split " ")
{
	$Url = "https://raw.githubusercontent.com/${Repository}/refs/heads/main/${TestDataPath}/${TestFile}"

	Invoke-WebRequest -Uri ${Url} -OutFile "${TestInputDirectory}\${TestSet}\${TestFile}"
}

