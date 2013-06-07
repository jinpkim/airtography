#ifdef WIN32
#include <windows.h>
#endif

#include "world.h"
#include "track.h"
#include "multitrack.h"
#include "filereadmultitrack.h"
#include "fileread.h"
#include "fileshow.h"
#include "filewritemultitrack.h"
using namespace jdksmidi;

#include "WordtoInt.h"
#include "RSAEncrypter.h"
#include <iostream>
#include "RSA.H"
#include "MPUINT.H"

using namespace std;

const unsigned int MAX_MPUINT_LEN = 32;
const char *rsa_d = "3944468182306490129890668128064166282888079664881759058485822932535889194050612552881100935547024572480766043979477430280352683150981569778761095649256861";
const char *rsa_e = "2059401299394647702106117656899229530707170303380700778668875719255199099359609820845614887146444406353484725021121780926979946947620426792867529081508741";
const char *rsa_n = "5976422441365186438016701355398741256152489884652994504696330715375530622839572107040284724219589165254936455575947087089199768690286896908774443748874051";

int WriteMidi(WordInt* wti, char* filepath);
void ConcateArgvStr(int argc, char* argv[], char* input, char* filepath);

int main(int argc, char** argv)
{
	int ret=0, input_len = 0;
	mpuint result(MAX_MPUINT_LEN), source(MAX_MPUINT_LEN);
	mpuint d(MAX_MPUINT_LEN), e(MAX_MPUINT_LEN), n(MAX_MPUINT_LEN);
	char* input = new char[256];
	WordInt* wti = new WordInt();
	RSAEncrypter* rsa = new RSAEncrypter();
	//Beep(200,50);
	char* filepath = new char[256];
	//cout << "Type Message : ";
	//cin.getline(input,'\\n');

	//no input argument -> exit
	if (argc < 3) {
		cout << "Should input command argument\n(project properties -> debugging -> command arguments)\nex)hello world e:\\\\temp\n";
		return 1;
	}

	ConcateArgvStr(argc, argv, input, filepath);


	char *c = new char[512];
	e.scan(rsa_e);
	n.scan(rsa_n);
	d.scan(rsa_d);

	/*d = 8;
	GenerateKeys(d, e, n);*/
	
	//EncryptDecrypt(result, source, d, n); //encrypt
	//EncryptDecrypt(source, result, e, n);	//decrypt

	mpuint mpuinput = wti->GetMpuint(input, MAX_MPUINT_LEN, &input_len);
	EncryptDecrypt(result, mpuinput, e, n);
	wti->Converter(result, input_len);
	
	//wti->Converter(input);
	//wti->printArray(wti->intArray);

	//publick key : 53, private key : 53
	//rsa->PrepareRSA(3, 37, 53);
	//wti->intArray = rsa->Encrypt(wti->intArray, wti->size);
	//wti->intArray = rsa->Decrypt(wti->intArray, wti->size);


	ret = WriteMidi(wti, filepath);
	wti->~WordInt();
	return 0;
}

//last argv is filepath
void ConcateArgvStr(int argc, char* argv[], char* input, char* filepath)
{
	int i = 1;

	strcpy(input, argv[1]);
	do {
		if (++i >= argc - 1) {
			break;
		}
		strcat(input, " ");
		strcat(input, argv[i]);
	}
	while (i < argc - 1);
	strcpy(filepath, argv[i]);

	return;
}

int WriteMidi(WordInt* wti, char* filepath)
{
	int return_code = -1;

    MIDITimedBigMessage m; // the object for individual midi events
    unsigned char chan, // internal midi channel number 0...15 (named 1...16)
        note, velocity, ctrl, val;

    MIDIClockTime t; // time in midi ticks
    MIDIClockTime dt = 20; // time interval (100 = 1 second)
    int clks_per_beat = 100; // number of ticks in crotchet (1...32767)
    int num_tracks = 2; // tracks 0 and 1

    MIDIMultiTrack tracks( num_tracks );  // the object which will hold all the tracks
    tracks.SetClksPerBeat( clks_per_beat );
    int trk; // track number, 0 or 1

    t = 0;
    m.SetTime( t );

    // track 0 is used for tempo and time signature info, and some other stuff

    trk = 0;
	m.SetTimeSig( 4, 2 ); // measure 4/4 (default values for time signature)
    tracks.GetTrack( trk )->PutEvent( m );

    int tempo = 1000000; // set tempo to 1 000 000 usec = 1 sec in crotchet
    // with value of clks_per_beat (100) result 10 msec in 1 midi tick
    // If no tempo is define, 120 beats per minute is assumed.

    // m.SetTime( t ); // do'nt need, because previous time is not changed
    m.SetTempo( tempo );
    tracks.GetTrack( trk )->PutEvent( m );

    // META_TRACK_NAME text in track 0 music notation software like Sibelius uses as headline of the music
    tracks.GetTrack( trk )->PutTextEvent(t, META_TRACK_NAME, "0day");

    // create cannal midi events and add them to a track 1
    trk = 1;

    // META_TRACK_NAME text in tracks >= 1 Sibelius uses as instrument name (left of staves)
    tracks.GetTrack( trk )->PutTextEvent(t, META_TRACK_NAME, "Church Organ");

	m.SetControlChange ( chan = 0, ctrl = 0xA, val = 0 ); // channel 0 panorama = 0 at the left
    tracks.GetTrack( trk )->PutEvent( m );

    // we change musical instrument in channels 0-2

    m.SetProgramChange( chan = 0, val = 19 ); // channel 0 instrument 19 - Church Organ
    tracks.GetTrack( trk )->PutEvent( m );

	t = 0;

    // we add note 1: press and release in (dt) ticks

	for(int i=0; i<wti->size;i++)
	{
		m.SetTime( t );
		m.SetNoteOn( chan = 0, note = wti->intArray[i], velocity = 100 );
		tracks.GetTrack( trk )->PutEvent( m );

    // after note(s) on before note(s) off: add words to music in the present situation
		tracks.GetTrack( trk )->PutTextEvent(t, META_LYRIC_TEXT, "Centre");

		m.SetTime( t += dt );
		m.SetNoteOff( chan, note, velocity );
		m.SetNoteOff( chan, note, velocity );
    // alternative form of note off event: useful to reduce midifile size if running status is used (on default so)
    // m.SetNoteOn( chan, note, 0 );
		tracks.GetTrack( trk )->PutEvent( m );
	}
	const char *outfile_name = strcat(filepath,"\\junkmidifile.mid");
	//printf("%s\n", outfile_name);
    MIDIFileWriteStreamFileName out_stream( outfile_name );

    // then output the stream like my example does, except setting num_tracks to match your data

    if( out_stream.IsValid() )
    {
        // the object which takes the midi tracks and writes the midifile to the output stream
        MIDIFileWriteMultiTrack writer( &tracks, &out_stream );

        // write the output file
        if ( writer.Write( num_tracks ) )
        {
            cout << "\nOK writing file " << outfile_name << endl;
            return_code = 0;
        }
        else
        {
            cerr << "\nError writing file " << outfile_name << endl;
        }
    }
    else
    {
        cerr << "\nError opening file " << outfile_name << endl;
    }
    return return_code;
}
