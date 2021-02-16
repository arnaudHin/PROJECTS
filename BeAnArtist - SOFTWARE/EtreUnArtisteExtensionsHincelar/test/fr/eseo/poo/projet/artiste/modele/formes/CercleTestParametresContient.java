package fr.eseo.poo.projet.artiste.modele.formes;

import static org.junit.Assert.assertEquals;

import java.util.Arrays;
import java.util.Collection;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;

import fr.eseo.poo.projet.artiste.modele.Coordonnees;

@RunWith(Parameterized.class)
public class CercleTestParametresContient {
	
	private Coordonnees position; 
	private double taille; 
	private Coordonnees coordContient; 
	private boolean contient;
	
	public CercleTestParametresContient(Coordonnees position, double taille, Coordonnees coordContient, boolean contient) {
		this.position = position; 
		this.taille = taille; 
		this.coordContient = coordContient; 
		this.contient = contient;
	}
	@Parameters(name= "dataCercle[{index}] : {0}, {1}, {2}, {3}") 
	public static Collection<Object[]>dataCercle(){
		Object[][] dataCercle = new Object[][] {
			{new Coordonnees(10, 10), 5, new Coordonnees(12.5, 12.5), true},
			{new Coordonnees(10, 10), 5, new Coordonnees(10, 10), false},
			{new Coordonnees(10, 10), 5, new Coordonnees(12.5, 10), true},
			{new Coordonnees(10, 10), 5, new Coordonnees(15, 12.6), false},
			{new Coordonnees(10, 10), 5, new Coordonnees(14.9, 12.5), true},
			{new Coordonnees(10, 10), 5, new Coordonnees(12.5, 10.1), true},
			{new Coordonnees(2.3, 5.6), 9.6, new Coordonnees(3.2, 4.8+5.6), true}
			
		};
		return Arrays.asList(dataCercle);}
	
	@Test
	public void testContient() {
		CercleTestParametresContient testcontient = new CercleTestParametresContient(position, taille, coordContient, contient);
		Cercle cercle1 = new Cercle(testcontient.position, testcontient.taille);
		assertEquals("Le point est bien contenu dans le cercle", contient, cercle1.contient(coordContient));

		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	


}
