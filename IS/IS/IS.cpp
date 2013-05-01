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


using namespace std;

int WriteMidi(WordInt* wti);

int main()
{
	int ret=0;
	char* input = new char[256];
	WordInt* wti = new WordInt();
	RSAEncrypter* rsa = new RSAEncrypter();
	//Beep(200,50);
	

	cout << "Type Message : ";
	cin.getline(input,'\\n');
	wti->Converter(input);
	//wti->printArray(wti->intArray);

	//publick key : 53, private key : 53
	rsa->PrepareRSA(3, 37, 53);
	wti->intArray = rsa->Encrypt(wti->intArray, wti->size);
	//wti->intArray = rsa->Decrypt(wti->intArray, wti->size);


	ret = WriteMidi(wti);
	wti->~WordInt();
	return 0;
}

int WriteMidi(WordInt* wti)
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

	const char *outfile_name = "create_midifile.mid";
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
	system("pause");
    return return_code;
}